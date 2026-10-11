#include "common.hpp"

#include <cassert>

struct alignas(8) LifeTime {
  LifeTime() { PRINT_CALL(); }
  ~LifeTime() { PRINT_CALL(); }
  
  char field{};
};

/* Unaligned */
template<typename T>
class ArenaAllocator {
public:
  explicit ArenaAllocator(void* const buf, const size_t size)
    : _buf {static_cast<std::byte*>(buf)}
    , _sz {size}
  {}

  T* allocate(const size_t count) {
    if (_offset + count > _sz)
      throw std::bad_alloc{};

    T* ptr = static_cast<T*>(static_cast<void*>((_buf + _offset)));
    _offset += count;
    return ptr;
  }

  void deallocate(T* const ptr) {}

  template<typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    new (ptr) U{std::forward<Args>(args)...};
  }

  void destroy(T* ptr) {
    ptr->~T();
  }

private:
  std::byte* _buf {nullptr};
  size_t _sz {0};
  size_t _offset {0};
};

int main() {
  std::array<char, 1024> arr;
  ArenaAllocator<LifeTime> a_alloc {arr.data(), arr.size()};
  LifeTime* ptr = a_alloc.allocate(sizeof(LifeTime));
  a_alloc.construct(ptr);
  a_alloc.destroy(ptr);
  a_alloc.deallocate(ptr); // no-op
}