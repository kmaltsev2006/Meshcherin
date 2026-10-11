#include "common.hpp"

#include <utility>

template<typename Key, typename Value>
class UnorderedMap {

  struct NodeBase {
    NodeBase(NodeBase* const next=nullptr)
      : next{next}
    {} 

    NodeBase* next {nullptr};
  };
  
  struct Node : NodeBase {
    explicit Node(const uint64_t hash, const std::pair<Key, Value>& kv)
      : hash{hash}
      , kv{kv}
    {}

    uint64_t hash;
    std::pair<const Key, Value> kv;
  };

  template<bool is_const>
  class BaseIterator {
  public:
    using difference_type = size_t;
    using value_type = std::conditional_t<is_const, std::pair<const Key, Value>, const std::pair<const Key, Value>>;
    using reference = std::conditional_t<is_const, const value_type&, value_type&>;
    using pointer = std::conditional_t<is_const, const value_type*, value_type*>;
    using iterator_category = std::forward_iterator_tag;

  public:
    explicit BaseIterator(NodeBase* const ptr)
      : _ptr{ptr}
    {}

    reference operator*() const {
      return static_cast<Node*>(_ptr)->kv;
    }

    pointer operator->() const {
      return _ptr;
    }

    bool operator==(const BaseIterator& rhs) const {
      return _ptr == rhs._ptr;
    }

    bool operator!=(const BaseIterator& rhs) const {
      return !(*this == rhs);
    }

    BaseIterator& operator++() {
      _ptr = _ptr->next;
      return *this;
    }

    BaseIterator operator++(int) {
      BaseIterator tmp {*this};
      ++(*this);
      return tmp;
    }

  private:
    NodeBase* _ptr;
  };

public:
  using Iterator = BaseIterator<false>;
  using ConstIterator = BaseIterator<true>;

public:
  ~UnorderedMap() {
    NodeBase* node = _dummy_ptr->next;
    while (node != _dummy_ptr) {
      Node* tmp = static_cast<Node*>(node);
      node = node->next;
      delete tmp;
    }
    delete[] _buckets;
  }

  bool contains(const Key& key) const {
    if (_cap == 0) { return false; }

    const size_t i = _hash(key) % _cap;

    NodeBase* node = _buckets[i];
    if (!node) { return false; }

    while (true) {
      if (node->next == _dummy_ptr) { return false; }
      if (i != static_cast<Node*>(node->next)->hash % _cap) { return false; }
      if (equal_to(key, static_cast<Node*>(node->next)->kv.first)) { break; }
      node = node->next;
    }
    return true;
  }

  double loadFactor() {
    return _cap != 0 ? _sz / _cap : 1.0;
  }

  void insert(const std::pair<Key, Value>& kv) {
    if (contains(kv.first)) { return; }

    if (loadFactor() > kMaxLoadFactor) {
      _rehash(_cap != 0 ? _cap * 2 : 1);
    }

    Node* new_node = new Node {_hash(kv.first), kv};
    _insert(new_node, _buckets, _cap);
    ++_sz;
  }

  void erase(const Key& key) {
    if (_cap == 0) { return; }

    size_t i = _hash(key) % _cap;

    NodeBase* node = _buckets[i];
    if (!node) { return; }

    while (true) {
      if (node->next == _dummy_ptr) { return; }
      if (static_cast<Node*>(node->next)->hash % _cap != i) { return; }
      if (equal_to(key, static_cast<Node*>(node->next)->kv.first)) { break; }
      node = node->next;
    }

    if (node->next->next != _dummy_ptr) {
      size_t next_hash = static_cast<Node*>(node->next->next)->hash;
      if (i != next_hash % _cap) {
        _buckets[next_hash % _cap] = node;
        if (node == _buckets[i]) {
          _buckets[i] = nullptr;
        }
      }
    }
    if (node->next->next == _dummy_ptr && node == _buckets[i]) {
      _buckets[i] = nullptr;
    }

    Node* tmp = static_cast<Node*>(node->next);
    node->next = node->next->next;
    delete tmp;
    --_sz;
  }

  Iterator begin() { return Iterator{_dummy_ptr->next}; };
  Iterator end() { return Iterator{_dummy_ptr}; };
  ConstIterator begin() const { return ConstIterator{_dummy_ptr}; };
  ConstIterator end() const { return ConstIterator{_dummy_ptr}; };
  ConstIterator cbegin() const { return ConstIterator{_dummy_ptr}; };
  ConstIterator cend() const { return ConstIterator{_dummy_ptr}; };

private:
  std::hash<Key> _hash;
  std::equal_to<Key> equal_to;
  NodeBase _dummy{&_dummy};
  
  NodeBase** _buckets {nullptr};
  NodeBase* _dummy_ptr {&_dummy};
  size_t _cap {0};
  size_t _sz {0};
  static constexpr double kMaxLoadFactor {0.75};

private:
  void _insert(Node* const new_node, NodeBase** const buckets, const size_t cap) {
    const size_t i = new_node->hash % cap;

    if (buckets[i]) {
      new_node->next = buckets[i]->next;
      buckets[i]->next = new_node;
    } else {
      if (_dummy_ptr->next != _dummy_ptr) {
        buckets[static_cast<Node*>(_dummy_ptr->next)->hash % cap] = new_node;
      }
      new_node->next = _dummy_ptr->next;
      _dummy_ptr->next = new_node;
      buckets[i] = _dummy_ptr;
    }
  }

  void _rehash(const size_t new_cap) {
    NodeBase** new_buckets = new NodeBase*[new_cap]{nullptr};
    NodeBase* node = _dummy_ptr->next;
    _dummy_ptr->next = _dummy_ptr;
    while (node != _dummy_ptr) {
      NodeBase* next = std::exchange(node->next, nullptr);
      _insert(static_cast<Node*>(node), new_buckets, new_cap);
      node = next;
    }
    delete[] _buckets;
    _buckets = new_buckets;
    _cap = new_cap;
  }
};

int main() {
  UnorderedMap<int, int> um;
  um.insert({14, 52});
  um.insert({90, 38});
  um.insert({56, 14});
  um.erase(14);
  um.insert({57, 0});
  um.insert({93, 38});
  um.erase(51);
  um.insert({85, 98});
  um.insert({95, 6});
  um.insert({92, 5});
  um.erase(11);
  um.insert({58, 99});
  um.insert({20, 86});
  um.contains(31);

  for (const auto& [key, value] : um) {
    std::print("{} {}\n", key, value);
  }
}