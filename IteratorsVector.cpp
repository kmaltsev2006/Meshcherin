#include "common.hpp"

#include <utility>
#include <type_traits>
#include <iterator>
#include <vector>

class LifeTime {
public:
  explicit LifeTime(const size_t id) : _id{id} { PRINT_CALL(); }
  LifeTime(const LifeTime& rhs) noexcept
    : _id{rhs._id}
  { PRINT_CALL(); }
  
  LifeTime(LifeTime&& rhs) noexcept
    : _id{std::exchange(rhs._id, size_t{})}
  { PRINT_CALL(); }
  
  ~LifeTime() { PRINT_CALL(); }

  size_t id() const noexcept {
    return _id;
  }

private:
  size_t _id;
};

std::ostream& operator<<(std::ostream& os, const LifeTime& lt) {
  os << lt.id();
  return os;
}

template<typename T>
class Vector {

  template<bool is_const>
  class IteratorBase {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::conditional_t<is_const, T, const T>;
    using difference_type = size_t;
    using pointer = std::conditional_t<is_const, T*, const T*>;
    using reference = std::conditional_t<is_const, T&, const T&>;

  public:
    explicit IteratorBase(T* const ptr)
      : _ptr{ptr}
    {}

    reference operator*() const { return *_ptr; }

    pointer operator->() const { return _ptr; }

    bool operator==(const IteratorBase& rhs) {
      return _ptr == rhs._ptr;
    }

    bool operator!=(const IteratorBase& rhs) {
      return !(*this == rhs);
    }

    IteratorBase& operator++() {
      ++_ptr;
      return *this;
    }

    IteratorBase operator++(int) {
      IteratorBase tmp {*this};
      ++(*this);
      return tmp;
    }

    IteratorBase operator--() {
      --_ptr;
      return *this;
    }

    IteratorBase operator--(int) {
      IteratorBase tmp {*this};
      --(*this);
      return tmp;
    }

  private:
    T* _ptr;
  };

public:
  using Iterator = IteratorBase<false>;
  using ConstIterator = IteratorBase<true>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
public:
  ~Vector() {
    for (size_t i = 0; i < _sz; ++i) {
      _buf[i].~T();
    }
    delete[] std::bit_cast<std::byte*>(_buf);
  }

  size_t size() const { return _sz; }

  T& operator[](const size_t i) { return _buf[i]; }

  Iterator begin() { return Iterator{_buf}; }
  Iterator end() { return Iterator{_buf + _sz}; }

  ConstIterator begin() const { return ConstIterator{_buf}; }
  ConstIterator end() const { return ConstIterator{_buf + _sz}; }

  ConstIterator cbegin() const { return ConstIterator(_buf); }
  ConstIterator cend() const { return ConstIterator(_buf + _sz); }


  ReverseIterator rbegin() { return ReverseIterator{end()}; }
  ReverseIterator rend() { return ReverseIterator{begin()}; }

  ConstReverseIterator rbegin() const { return ConstReverseIterator{end()}; }
  ConstReverseIterator rend() const { return ConstReverseIterator{begin()}; }

  ConstReverseIterator crbegin() const { return ConstReverseIterator(end()); }
  ConstReverseIterator crend() const { return ConstReverseIterator(begin()); }

  void pushBack(const T& obj) {
    if (_sz == _cap) {
      /* reserve */
      size_t new_cap = _cap == 0 ? 1 : _cap * 2;
      
      T* new_buf = std::bit_cast<T*>(new std::byte[sizeof(T) * new_cap]);

      size_t i = 0;
      try {
        for (; i < _sz; ++i) {
          new (new_buf + i) T{std::move_if_noexcept(_buf[i])}; 
        }
        new (new_buf + _sz) T{obj};
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          new_buf[i].~T();
        }
        delete[] std::bit_cast<std::byte*>(new_buf);
        throw;
      }

      for (size_t i = 0; i < _sz; ++i) {
        _buf[i].~T();
      }
      delete[] std::bit_cast<std::byte*>(_buf);

      _buf = new_buf;
      _cap = new_cap;
    } else {
      new (_buf + _sz) T{obj};
    }
    ++_sz;
  }

  void popBack() {
    _buf[_sz].~T();
    --_sz;
  }

private:
  T* _buf {nullptr};
  size_t _sz {0};
  size_t _cap {0};
};

int main() {
  Vector<LifeTime> v;
  v.pushBack(LifeTime{0});
  v.pushBack(LifeTime{1});
  v.pushBack(LifeTime{2});
  v.pushBack(LifeTime{3});
  v.pushBack(LifeTime{4});
  v.popBack();

  for (const auto& el : v) {
    std::cout << el << " ";
  }
  std::print("\n");

  std::for_each(v.cbegin(), v.cend(), [](const auto& el){std::cout << el << " ";});
  std::print("\n");
  
  for (auto it = v.rbegin(); it != v.rend(); ++it) {
    std::cout << *it << " ";
  }
  std::print("\n");

  std::for_each(v.crbegin(), v.crend(), [](const auto& el){std::cout << el << " ";});
  std::print("\n");

  {
    using it_category = typename std::iterator_traits<
      typename Vector<int>::Iterator
    >::iterator_category;

    std::print("Vector<int>::iterator category: {}\n", typeid(it_category).name()); 
  }
}