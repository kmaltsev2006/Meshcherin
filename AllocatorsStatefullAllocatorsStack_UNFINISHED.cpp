#include "common.hpp"

#include <memory>
#include <utility>
#include <algorithm>
#include <cassert>

#include <forward_list> // DEL

// Single chunk statefull allocator
template<typename T>
class StackAllocator {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;

public:
  template<typename Y>
  struct rebind {
    using other = StackAllocator<Y>;
  };

public:
  StackAllocator(void* ptr, size_t size)
    : _cur_buf{ptr}
    , _sz{size} 
    , _space{_sz}
  { PRINT_CALL(); }

  StackAllocator()
    : _own_buf {::operator new(_max_own_buf_sz)}
    , _cur_buf {_own_buf}
    , _sz{_max_own_buf_sz}
    , _space{_sz}
  { PRINT_CALL(); }

  StackAllocator(const StackAllocator& rhs)
    : _own_buf{::operator new(rhs._sz)}
    , _cur_buf{_own_buf}
    , _sz{rhs._sz}
    , _space{_sz}
  { PRINT_CALL(); }

  StackAllocator(StackAllocator&& rhs)
    : _own_buf{std::exchange(rhs._own_buf, nullptr)}
    , _cur_buf{std::exchange(rhs._cur_buf, nullptr)}
    , _sz{std::exchange(rhs._sz, 0)}
    , _space{std::exchange(rhs._space, 0)}
  { PRINT_CALL(); }

  template<typename Y>
  StackAllocator(const StackAllocator<Y>& rhs)
    : _own_buf{::operator new(rhs._sz)}
    , _cur_buf{_own_buf}
    , _sz{rhs._sz}
    , _space{_sz}
  { 
    std::print("ptr: {}\n", static_cast<void*>(_own_buf));
  
  PRINT_CALL(); }

  static StackAllocator select_on_container_copy_construction() {
    return StackAllocator{};
  }

  ~StackAllocator() {
    std::print("ptr: {}\n", static_cast<void*>(_own_buf));
    ::operator delete(_own_buf);
  }

  T* allocate(size_t count) {
    T* ptr = static_cast<T*>(std::align(alignof(T), sizeof(T) * count, _cur_buf, _space));
    if (!ptr)
      throw std::bad_alloc{};
    uintptr_t intptr = reinterpret_cast<uintptr_t>(ptr) + sizeof(T);
    _cur_buf = reinterpret_cast<void*>(intptr);
    _space -= sizeof(T);
    std::print("alloc {}\n", static_cast<void*>(ptr));
    return ptr;
  }

  void deallocate(void* ptr, size_t n) noexcept {
    uintptr_t intptr = reinterpret_cast<uintptr_t>(_cur_buf);
    intptr -= sizeof(T) * n;
    _cur_buf = reinterpret_cast<void*>(intptr);
    std::print("dealloc {}\n", static_cast<void*>(ptr));
    assert(_cur_buf == ptr); // DEL
  }

  template<typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    ::new (reinterpret_cast<void*>(ptr)) U{std::forward<Args>(args)...};
  }

  void destroy(T* ptr) noexcept {
    ptr->~T();
  }

// private:
  size_t _max_own_buf_sz {1 << 13};
  void* _own_buf {nullptr};
  void* _cur_buf {nullptr};
  size_t _sz {0};
  size_t _space {0};
};

template<typename T, typename Alloc=std::allocator<T>>
class ForwardList {
  struct NodeBase {
    NodeBase(NodeBase* next=nullptr)
      : next{next}
    {}

    NodeBase(const NodeBase& rhs) = delete;
    NodeBase(NodeBase&& rhs) = delete;

    NodeBase* next{nullptr};
  };

  struct Node : NodeBase {
    Node(const T& value, NodeBase* next=nullptr)
      : NodeBase{next}
      , value{value}
    {}

    Node(T&& value, NodeBase* next=nullptr)
      : NodeBase{next}
      , value{std::move(value)}
    {}

    Node(const Node& rhs) = delete;
    Node(Node&& rhs) = delete;

    T value;
  };

  template<bool is_const>
  class BaseIterator {
  public:
    using difference_type = size_t;
    using value_type = std::conditional_t<is_const, const T, T>;
    using pointer = std::conditional_t<is_const, const T*, T*>;
    using reference = std::conditional_t<is_const, const T&, T&>;
    using iterator_category = std::forward_iterator_tag;
  public:
    BaseIterator(NodeBase* ptr)
      : _ptr{ptr}
    {}

    T& operator*() const { 
      return static_cast<Node*>(_ptr)->value; }

    T* operator->() const { 
      return &static_cast<Node*>(_ptr)->value; }

    bool operator==(const BaseIterator& rhs) const
      { return _ptr == rhs._ptr; }
    
    bool operator!=(const BaseIterator& rhs) const
      { return !(*this == rhs); }

    BaseIterator& operator++() {
      _ptr = _ptr->next;
      return *this;
    }

    BaseIterator operator++(int) {
      NodeBase tmp {*this};
      ++(*this);
      return tmp;
    }

  private:
    NodeBase* _ptr{nullptr};
  };

  using alloc_t = typename std::allocator_traits<Alloc>::rebind_alloc<Node>;
  using alloc_traits = std::allocator_traits<alloc_t>;

public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = BaseIterator<false /* is_const */>;
  using const_iterator = BaseIterator<true /* is_const */>;
  using difference_type = size_t;
  using size_type = size_t;

public:
  ForwardList(Alloc alloc=Alloc{})
    // : _alloc{ allocator_traits<Alloc>:: alloc}
  {}

  template<typename InputIt>
  ForwardList(InputIt first, InputIt last) {
    NodeBase* cur = _dummy_ptr;
    for (InputIt it = first; it != last; ++it) {
      Node* new_node = alloc_traits::allocate(_alloc, 1);
      try {
        alloc_traits::construct(_alloc, new_node, *it);
      } catch(...) {
        alloc_traits::deallocate(_alloc, new_node, 1);
        throw;
      }
      cur->next = new_node;
      cur = cur->next;
    }
    cur->next = _dummy_ptr;
    _prev_end = cur;
  }

  ForwardList(const ForwardList& rhs)
    : ForwardList(rhs.begin(), rhs.end())
  {}

  ForwardList(ForwardList&& rhs) {
    if (rhs.empty()) { return; }
    _dummy_ptr->next = std::exchange(rhs._dummy_ptr->next, rhs._dummy_ptr);
    _prev_end = std::exchange(rhs._prev_end, rhs._dummy_ptr);
    _prev_end->next = _dummy_ptr;
  }

  ForwardList& operator=(const ForwardList& rhs) {
    if (this == &rhs) { return *this; }
    ForwardList tmp{rhs};
    swap(tmp);
    return *this;
  }

  ForwardList& operator=(ForwardList&& rhs) {
    if (this == &rhs) { return *this; }
    ForwardList tmp{std::move(rhs)};
    swap(tmp);
    return *this;
  }

  ~ForwardList() {
    while (!empty())
      pop_front();
  }

  inline bool empty() const { return _dummy_ptr->next == _dummy_ptr; }

  void push_front(const T& value) {
    Node* new_node = alloc_traits::allocate(_alloc, 1);
    try {
      alloc_traits::construct(_alloc, new_node, value, _dummy_ptr->next);
      if (empty()) { _prev_end = new_node; }
    } catch(...) {
      alloc_traits::deallocate(_alloc, new_node, 1);
      throw;
    }
    _dummy_ptr->next = new_node;
  }

  void push_front(T&& value) {
    Node* new_node = alloc_traits::allocate(_alloc, 1);
    try {
      alloc_traits::construct(_alloc, new_node, std::move(value), _dummy_ptr->next);
      if (empty()) { _prev_end = new_node; }
    } catch(...) {
      alloc_traits::deallocate(_alloc, new_node, 1);
      throw;
    }
    _dummy_ptr->next = new_node;
  }

  template<typename... Args>
  void emplace_front(Args&&... args) {
    Node* new_node = alloc_traits::allocate(_alloc, 1);
    try {
      alloc_traits::construct(_alloc, new_node, std::forward<Args>(args)..., _dummy_ptr->next);
      if (empty()) { _prev_end = new_node; }
    } catch(...) {
      alloc_traits::deallocate(_alloc, new_node, 1);
      throw;
    }
    _dummy_ptr->next = new_node;
  }

  void pop_front() {
    Node* tmp = static_cast<Node*>(_dummy_ptr->next);
    _dummy_ptr->next = tmp->next;
    alloc_traits::destroy(_alloc, tmp);
    alloc_traits::deallocate(_alloc, tmp, 1);
    if (empty()) { _prev_end = _dummy_ptr; }
  }

  bool operator==(const ForwardList& rhs) {
    return std::equal(begin(), end(), rhs.begin());
  }

  bool operator!=(const ForwardList& rhs) {
    return !(*this == rhs);
  }

  void swap(ForwardList& rhs) {
    swap(*this, rhs);
  }

  iterator begin() { return iterator{_dummy_ptr->next}; }
  iterator end() { return iterator{_dummy_ptr}; }
  const_iterator begin() const { return const_iterator{_dummy_ptr->next}; }
  const_iterator end() const { return const_iterator{_dummy_ptr}; }
  const_iterator cbegin() const { return const_iterator{_dummy_ptr->next}; }
  const_iterator cend() const { return const_iterator{_dummy_ptr}; }

private:
  [[no_unique_address]] alloc_t _alloc;
  NodeBase _dummy{&_dummy};
  NodeBase* _dummy_ptr{&_dummy};
  NodeBase* _prev_end{_dummy_ptr};

private:
  static void swap(ForwardList& lhs, ForwardList& rhs) {
    if (lhs.empty() && rhs.empty()) return;

    if (!lhs.empty() && !rhs.empty()) {
      std::swap(lhs._dummy_ptr->next, rhs._dummy_ptr->next);
      std::swap(lhs._prev_end->next, rhs._prev_end->next);
      std::swap(lhs._prev_end, rhs._prev_end);
      return;
    }

    ForwardList* l = &lhs;
    ForwardList* r = &rhs;

    if (r->empty()) { std::swap(l, r); }
    
    /* l->empty() == true */

    l->_dummy_ptr->next = std::exchange(r->_dummy_ptr->next, r->_dummy_ptr);
    l->_prev_end = std::exchange(r->_prev_end, r->_dummy_ptr);
    l->_prev_end->next = l->_dummy_ptr;
  }
};


struct alignas(32) LifeTime {
  // LifeTime() : id{next_id++} { std::print("ctor {}\n", id); }
  // ~LifeTime() { std::print("dtor {}\n", id); }

  size_t id{0};
  inline static size_t next_id{0};
};


int main() {
  std::byte mbr[1024];
  StackAllocator<LifeTime> alloc{mbr, sizeof(mbr)};

  std::allocator<LifeTime> alloc2;
  std::forward_list<LifeTime, decltype(alloc)> v{alloc};

  std::print("{}\n", sizeof(LifeTime));

  // v.emplace_front();
  // v.emplace_front();
  // v.emplace_front();
  // v.pop_front();
  // v.pop_front();
  // v.emplace_front();
  // v.emplace_front();
  // v.emplace_front();

  // v.pop_front();

  // auto x = v;
  // v.emplace_front();
  // v.pop_front();
  // v.pop_front();
  // // x.pop_front();

  // std::print("\n");
}