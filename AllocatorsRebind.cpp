#include "common.hpp"

#include <utility>
#include <forward_list>

struct LifeTime {
  explicit LifeTime(const size_t id) : id{id} { PRINT_CALL(); }
  LifeTime(const LifeTime& rhs) : id{rhs.id} { PRINT_CALL(); }
  LifeTime(LifeTime&& rhs) : id{std::exchange(rhs.id, {})}{ PRINT_CALL(); }
  ~LifeTime() { PRINT_CALL(); }
  size_t id;
};

std::ostream& operator<<(std::ostream& os, const LifeTime& lt) {
  os << lt.id;
  return os;
}

template<typename T>
struct Allocator {
  template<typename Y>
  struct rebind {
    using other = Allocator<Y>;
  };

  T* allocate(const size_t count) const {
    return static_cast<T*>(::operator new(count));
  }

  void deallocate(T* const ptr) const {
    delete ptr;
  }

  template<typename Y, typename... Args>
  void construct(Y* const ptr, Args&&... args) const {
    new (ptr) Y{std::forward<Args>(args)...};
  }

  void destroy(T* const ptr) const {
    ptr->~T();
  }

  template<typename U>
  bool operator==(const Allocator<U>& rhs) const
    { return true; }

  template<typename U>
  bool operator!=(const Allocator<U>& rhs) const
    { return false; }
};

template<typename T, typename Alloc=std::allocator<T>>
class ForwardList {
  struct NodeBase {
    explicit NodeBase(NodeBase* const next)
      : next{next}
    {}

    NodeBase* next{nullptr};
  };

  struct Node : NodeBase {
    explicit Node(const T& value, NodeBase* const next=nullptr)
      : NodeBase{next}
      , value{value}
    {}
    T value;
  };

  template<bool is_const>
  class BaseIterator {
  public:
    using difference_type = size_t;
    using value_type = std::conditional_t<is_const, const T, T>;
    using reference = std::conditional_t<is_const, const T&, T&>;
    using pointer = std::conditional_t<is_const, const T*, T*>;
    using iterator_category = std::forward_iterator_tag;

  public:
    BaseIterator(NodeBase* const ptr)
      : _ptr{ptr}
    {}

    bool operator==(const BaseIterator& rhs) const {
      return _ptr == rhs._ptr;
    }

    bool operator!=(const BaseIterator& rhs) const {
      return !(*this == rhs);
    }

    reference operator*() const {
      return static_cast<Node*>(_ptr)->value;
    }

    pointer operator->() const {
      return &static_cast<Node*>(_ptr)->value;
    }

    BaseIterator& operator++() {
      _ptr = _ptr->next;
      return *this;
    }

    BaseIterator operator++(int) {
      Iterator tmp {*this};
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
  ~ForwardList() {
    while (!empty()) {
      popFront();
    }
  }

  size_t empty() const { return _sz == 0; }
  
  size_t size() const { return _sz; }

  void pushFront(const T& value) {
    Node* new_node = alloc.allocate(sizeof(Node));
    alloc.construct(new_node, value, _dummy_ptr->next);
    _dummy_ptr->next = new_node;
    ++_sz;
  }

  void popFront() {
    Node* tmp = static_cast<Node*>(_dummy_ptr->next);
    _dummy_ptr->next = tmp->next;
    alloc.destroy(tmp);
    alloc.deallocate(tmp);
    --_sz;
  }

  Iterator begin() { return Iterator{_dummy_ptr->next}; }
  Iterator end() { return Iterator{_dummy_ptr}; }  
  ConstIterator begin() const { return Iterator{_dummy_ptr->next}; }
  ConstIterator end() const { return Iterator{_dummy_ptr}; }
  ConstIterator cbegin() const { return ConstIterator{_dummy_ptr->next}; }
  ConstIterator cend() const { return ConstIterator{_dummy_ptr}; }
  
private:
  [[no_unique_address]] typename Alloc::rebind<Node>::other alloc;
  NodeBase _dummy {&_dummy};
  NodeBase* _dummy_ptr {&_dummy};
  size_t _sz {0};
};

int main() {
  constexpr size_t kIter {10}; 

  ForwardList<LifeTime, Allocator<LifeTime>> l;
  for (size_t i = 0; i < kIter; ++i) {
    l.pushFront(LifeTime{i});
  }
  for (size_t i = 0; i < kIter / 2; ++i) {
    l.popFront();
  }
  for (const auto& el : l) {
    std::cout << el << " ";
  }
  std::print("\n");
}