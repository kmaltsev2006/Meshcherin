/**
 * Exception safety levels:
 * 1) nothrow (will never throw)
 * 2) strong (program state will be rollbacked to state right before function call that thrown)
 * 3) basic (program state will be valid, but might be changed)
 * 4) no guarantee
 */
/**
 * new(ptr) T{}   \
 * and            | - placement new 
 * new(ptr) T[]{} /
 */
#include "common.hpp"

#include <cstddef>
#include <utility>

class LifeTime {
friend std::ostream& operator<<(std::ostream& os, const LifeTime& lt);

public:
  explicit LifeTime(size_t id) : _id {id} { PRINT_CALL(); }

  LifeTime(const LifeTime& rhs) : _id {rhs._id} { PRINT_CALL(); }

  LifeTime(LifeTime&& rhs) noexcept
    : _id {std::exchange(rhs._id, size_t{})}
  { PRINT_CALL(); }

  ~LifeTime() { PRINT_CALL(); }

private:
  size_t _id;
};

std::ostream& operator<<(std::ostream& os, const LifeTime& lt) {
  os << lt._id;
  return os;
}

template<typename T>
class Vector {
public:
  ~Vector() {
    for (size_t i = 0; i < _sz; ++i) {
      _buf[i].~T();
    }
    delete[] std::bit_cast<std::byte*>(_buf);
  }

  T& operator[](size_t i) { return _buf[i]; }

  size_t size() const { return _sz; }

  void pushBack(const T& obj) {
    if (_sz == _cap) {
      /* reserve */
      size_t new_cap = _cap == 0 ? 1 : _cap * 2;

      T* new_buf = std::bit_cast<T*>(new std::byte[sizeof(T) * new_cap]);

      size_t i = 0;
      try {
        for (; i < _sz; ++i) {
          new (&new_buf[i]) T{std::move_if_noexcept(_buf[i])};
        }
        new (&new_buf[_sz]) T{obj};
      } catch(...) {
        for (size_t j = 0; j < i; ++j) {
          new_buf[j].~T();
        }
        delete[] new_buf;
        throw;
      }

      for (size_t i = 0; i < _sz; ++i) {
        _buf[i].~T();
      }
      delete[] std::bit_cast<std::byte*>(_buf);

      _cap = new_cap;
      _buf = new_buf;
    } else {
      new (&_buf[_sz]) T{obj};
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
  for (size_t i = 0; i < 5; ++i) {
    v.pushBack(LifeTime{i});
  }
  for (size_t i = 0; i < 2; ++i) {
    v.popBack();
  }

  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::print("\n");
}