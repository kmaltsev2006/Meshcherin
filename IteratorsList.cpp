#include "common.hpp"

#include <iterator>

template<typename T>
class List {

  struct NodeBase {
    NodeBase(NodeBase* prev, NodeBase* next) : prev{prev}, next{next} {}
    
    NodeBase() : NodeBase{this, this} {}

    NodeBase* prev;
    NodeBase* next;
  };

  struct Node : NodeBase {
    Node(const T& val)
      : NodeBase{nullptr, nullptr}
      , val{val}
    {}

    T val;
  };

  template<bool is_const>
  class BaseIterator {
  public:
    using difference_type = size_t;
    using value_type = std::conditional_t<is_const, const T, T>;
    using pointer = std::conditional_t<is_const, const T*, T*>;
    using reference = std::conditional_t<is_const, const T&, T&>;
    using iterator_category = std::bidirectional_iterator_tag;

  public:
    explicit BaseIterator(NodeBase* const ptr)
      : _ptr{ptr}
    {}

    BaseIterator(const BaseIterator&) = default;
    BaseIterator& operator=(const BaseIterator&) = default;

    bool operator==(const BaseIterator& rhs) const {
      return _ptr == rhs._ptr;
    }

    bool operator!=(const BaseIterator& rhs) const {
      return !(*this == rhs);
    }

    reference operator*() const {
      return static_cast<Node*>(_ptr)->val;
    }

    pointer operator->() const {
      return &static_cast<Node*>(_ptr)->val;
    }

    BaseIterator& operator++() {
      _ptr = _ptr->next;
      return *this;
    }

    BaseIterator& operator++(int) {
      BaseIterator tmp{*this};
      ++(*this);
      return tmp;
    }

    BaseIterator& operator--() {
      _ptr = _ptr->prev;
      return *this;
    }

    BaseIterator& operator--(int) {
      BaseIterator tmp{*this};
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
  ~List() {
    while (!empty()) {
      popFront();
    }
  }

  inline size_t size() const noexcept { return _sz; }

  inline bool empty() const noexcept { return _sz == 0; }

  void pushBack(const T& value) {
    Node* new_node = new Node{value};

    if (empty()) {
      pushInEmpty(new_node);
    } else {
      new_node->prev = _dummy_ptr->prev;
      new_node->next = _dummy_ptr;
      _dummy_ptr->prev->next = new_node;
      _dummy_ptr->prev = new_node;
    }
    ++_sz;
  }

  void pushFront(const T& value) {
    Node* new_node = new Node{value};
    if (empty()) {
      pushInEmpty(new_node);
    } else {
      new_node->prev = _dummy_ptr;
      new_node->next = _dummy_ptr->next;
      _dummy_ptr->next->prev = new_node;
      _dummy_ptr->next = new_node;
    }
    ++_sz;
  }

  void popBack() {
    Node* tmp = static_cast<Node*>(_dummy_ptr->prev);

    if (size() == 1) {
      popLast();
    } else {
      _dummy_ptr->prev = tmp->prev;
      _dummy_ptr->prev->next = _dummy_ptr;
    }

    delete tmp;
    --_sz;
  }

  void popFront() {
    Node* tmp = static_cast<Node*>(_dummy_ptr->next);

    if (size() == 1) {
      popLast();
    } else {
      _dummy_ptr->next = tmp->next;
      _dummy_ptr->next->prev = _dummy_ptr;
    }

    delete tmp;
    --_sz;
  }
  
  Iterator begin() { return Iterator(_dummy_ptr->next); }
  Iterator end() { return Iterator(_dummy_ptr); }

  ConstIterator begin() const { return ConstIterator(_dummy_ptr->next); }
  ConstIterator end() const { return ConstIterator(_dummy_ptr); }

  ConstIterator cbegin() const { return ConstIterator(_dummy_ptr->next); }
  ConstIterator cend() const { return ConstIterator(_dummy_ptr); }

  ReverseIterator rbegin() { return ReverseIterator(end()); }
  ReverseIterator rend() { return ReverseIterator(begin()); }

  ConstReverseIterator rbegin() const  { return ConstReverseIterator(end()); }
  ConstReverseIterator rend() const { return ConstReverseIterator(begin()); }

  ConstReverseIterator crbegin() const  { return ConstReverseIterator(end()); }
  ConstReverseIterator crend() const { return ConstReverseIterator(begin()); }


private:
  NodeBase _dummy;
  NodeBase* _dummy_ptr {&_dummy};
  size_t _sz {0};

private:
  void pushInEmpty(Node* const new_node) {
    new_node->prev = _dummy_ptr;
    new_node->next = _dummy_ptr;
    _dummy_ptr->prev = new_node;
    _dummy_ptr->next = new_node;
  }

  void popLast() {
    _dummy_ptr->prev = _dummy_ptr;
    _dummy_ptr->next = _dummy_ptr;
  }
};

int main() {
  List<int> l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushBack(3);
  l.pushFront(4);
  l.pushFront(5);
  l.popBack();
  l.pushFront(6);
  l.popFront();
  l.popFront();
  l.pushFront(7);
  l.pushFront(8);

  for (const auto& el : l) {
    std::print("{} ", el);
  }
  std::print("\n");

  for (auto rit = l.crbegin(); rit != l.crend(); ++rit) {
    std::print("{} ", *rit);
  }
  std::print("\n");
}