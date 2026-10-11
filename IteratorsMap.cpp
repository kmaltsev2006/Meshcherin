#include "common.hpp"

#include <utility>
// #include <cassert>
#include <type_traits>

template<typename Key, typename Value, typename Cmp=std::less<Key>>
class Map /* BST */ {
  struct NodeBase {
    explicit NodeBase(NodeBase* const parent=nullptr)
      : parent {parent}
    {}

    // size_t h {0};
    NodeBase* parent {nullptr};
    NodeBase* left {nullptr};
    NodeBase* right {nullptr};
  };

  struct Node : NodeBase {
    explicit Node(const std::pair<Key, Value>& kv, NodeBase* parent)
      : NodeBase {parent}
      , kv {kv}
    {}

    std::pair<const Key, Value> kv;
  };

  template<bool is_const>
  class BaseIterator {
  public:
    using difference_type = size_t;
    using value_type = std::conditional_t<is_const, const std::pair<const Key, Value>, std::pair<const Key, Value>>;
    using reference = std::conditional_t<is_const, const value_type&, value_type&>;
    using pointer = std::conditional_t<is_const, const value_type*, value_type*>;
    using iterator_category = std::bidirectional_iterator_tag;

  public:
    explicit BaseIterator(NodeBase* const ptr)
      : _ptr {ptr}
    {}

    std::pair<const Key, Value>& operator*() const {
      return static_cast<Node*>(_ptr)->kv;
    }

    std::pair<const Key, Value>* operator->() const {
      return &static_cast<Node*>(_ptr)->kv;
    } 

    bool operator==(const BaseIterator& rhs) const {
      return _ptr == rhs._ptr;
    }

    bool operator!=(const BaseIterator& rhs) const {
      return !(*this == rhs);
    }

    BaseIterator& operator++() {
      if (!_ptr->right) {
        while (true) {
          if (_ptr->parent->left == _ptr) {
            _ptr = _ptr->parent;
            break;
          }
          _ptr = _ptr->parent;
        }
      } else {
        _ptr = _ptr->right;
        while (_ptr->left) {
          _ptr = _ptr->left;
        }
      }

      return *this;
    }

    BaseIterator operator++(int) {
      BaseIterator tmp {*this};
      ++(*this);
      return tmp;
    }

    BaseIterator& operator--() {
      if (!_ptr->left) {
        while (true) {
          if (_ptr->parent->right == _ptr) {
            _ptr = _ptr->parent;
            break;
          }
          _ptr = _ptr->parent;
        }
      } else {
        _ptr = _ptr->left;
        while (_ptr->right) {
          _ptr = _ptr->right;
        }
      }
      return *this;
    }

    BaseIterator operator--(int) {
      BaseIterator tmp {*this};
      --(*this);
      return tmp;
    }

  private:
    NodeBase* _ptr;
  };

public:
  using Iterator = BaseIterator<false>;
  using ConstIterator = BaseIterator<true>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
  ~Map() {
    if (_dummy.left)
      _clear(static_cast<Node*>(_dummy.left));
  }

  void insert(const std::pair<Key, Value>& kv) {
    if (!_dummy.left) {
      _dummy.left = new Node{kv, &_dummy};
      _begin = _dummy.left;
    } else {
      bool is_min = true;

      NodeBase* cur = _dummy.left;
      while (true) {
        if (_equal_to(kv.first, static_cast<Node*>(cur)->kv.first)) {
          break;
        } else if (_cmp(kv.first, static_cast<Node*>(cur)->kv.first)) {
          if (cur->left) {
            cur = cur->left;
          } else {
            cur->left = new Node{kv, cur};
            if (is_min) {_begin = cur->left;}
            break;
          }
        } else {
          is_min = false;
          if (cur->right) {
            cur = cur->right;
          } else {
            cur->right = new Node{kv, cur};
            break;
          }
        }
      }
    }
  }

  void erase(const Key& key) {
    if (_dummy.left) {
      bool is_min = true;
      NodeBase* cur = _dummy.left;
      while (true) {
        if (_equal_to(key, static_cast<Node*>(cur)->kv.first)) {
          if (cur->left && cur->right) {
            NodeBase* in_s = _getMin(cur->right);

            if (cur->right != in_s) {
              if (in_s->right) {
                in_s->right->parent = in_s->parent;
              }
              in_s->parent->left = in_s->right;
              in_s->right = cur->right;
              cur->right->parent = in_s;
            }

            in_s->left = cur->left;
            in_s->parent = cur->parent;
            cur->left->parent = in_s;

            _getParentLink(cur) = in_s;
          } else if (cur->left) {
            cur->left->parent = cur->parent;
            _getParentLink(cur) = cur->left;
          } else if (cur->right) {
            cur->right->parent = cur->parent;
            _getParentLink(cur) = cur->right;
            if (is_min) {_begin = _getMin(cur->right);}
          } else {
            _getParentLink(cur) = nullptr;
            if (is_min) {_begin = cur->parent;}
          }

          delete static_cast<Node*>(cur);
          break;
        } else if (_cmp(key, static_cast<Node*>(cur)->kv.first)) {
          if (!cur->left) break;
          cur = cur->left;
        } else {
          is_min = false;
          if (!cur->right) break;
          cur = cur->right;
        }
      }
    }
  }

  Iterator begin() { return Iterator{_begin}; };
  Iterator end() { return Iterator{_end}; };
  ConstIterator begin() const { return ConstIterator{_begin}; };
  ConstIterator end() const { return ConstIterator{_end}; };
  ConstIterator cbegin() const { return ConstIterator{_begin}; };
  ConstIterator cend() const { return ConstIterator{_end}; };

  ReverseIterator rbegin() { return ReverseIterator{end()}; };
  ReverseIterator rend() { return ReverseIterator{begin()}; };
  ConstReverseIterator rbegin() const { return ConstReverseIterator{end()}; };
  ConstReverseIterator rend() const { return ConstReverseIterator{begin()}; };
  ConstReverseIterator crbegin() const { return ConstReverseIterator{end()}; };
  ConstReverseIterator crend() const { return ConstReverseIterator{begin()}; };


private:
  NodeBase _dummy;
  NodeBase* _begin {&_dummy};
  NodeBase* _end {&_dummy};
  Cmp _cmp;
  std::equal_to<Key> _equal_to{};

private:
  void _clear(Node* const node) {
    // assert(node); // precondition
    
    if (node->left)
      _clear(static_cast<Node*>(node->left));

    if (node->right)
      _clear(static_cast<Node*>(node->right));
    
    delete node;
  }

  NodeBase* _getMin(NodeBase* const node) {
    NodeBase* cur = node;
    while (cur->left) {
      cur = cur->left;
    }
    return cur;
  }

  NodeBase*& _getParentLink(NodeBase* const node) {
    if (node->parent->left == node) {
      return node->parent->left;
    }
    return node->parent->right;
  }
};

int main() {
  Map<int, int> m;
  m.insert({4, 0});
  m.insert({1, 0});
  m.insert({3, 0});
  m.insert({6, 0});
  m.insert({5, 0});
  m.erase(4);
  m.insert({9, 0});
  m.erase(3);
  m.erase(1);
  m.insert({8, 0});
  m.insert({7, 0});
  
  for (const auto& [key, val] : m) {
    std::print("{} ", key);
  }
  std::print("\n");

  for (auto rit = m.crbegin(); rit != m.crend(); ++rit) {
    std::print("{} ", rit->first);
  }
  std::print("\n");
}