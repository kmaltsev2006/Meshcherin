/**
 * Allocator must have following methods:
 *
    T* allocate(const size_t count) const;
    void deallocate(T* ptr) const;
    void construct(Y* const ptr, Args&&... args) const;
    void destroy(T* const ptr) const;

    bool operator==(const Allocator<U>& other) const;
    bool operator!=(const Allocator<U>& other) const;
 *
 */

#include "common.hpp"

#include <utility>

struct LifeTime {
  explicit LifeTime(const size_t id) : id {id} { PRINT_CALL(); }
  LifeTime(const LifeTime& rhs) : id{rhs.id} { PRINT_CALL(); }
  LifeTime(LifeTime&& rhs) : id{std::exchange(rhs.id, {})} { PRINT_CALL(); }
  ~LifeTime() { PRINT_CALL(); }

  size_t id{};
};

template<typename T>
struct Allocator {
  T* allocate(const size_t count) const {
    return static_cast<T*>(::operator new(count));
  }

  void deallocate(T* const ptr) const {
    ::operator delete(ptr);
  }

  template<typename Y, typename... Args>
  void construct(Y* const ptr, Args&&... args) const {
    new (ptr) Y{std::forward<Args>(args)...};
  }

  void destroy(T* const ptr) const {
    ptr->~T();
  }

  template<typename U>
  bool operator==(const Allocator<U>& other) const
    { return true; }
  
  template<typename U>
  bool operator!=(const Allocator<U>& other) const
    { return false; }

};

int main() {
  Allocator<LifeTime> alloc;
  LifeTime* ptr = alloc.allocate(sizeof(LifeTime));
  alloc.construct(ptr, static_cast<size_t>(42));
  
  std::print("{}\n", ptr->id);
  
  alloc.destroy(ptr);
  alloc.deallocate(ptr);

  std::print("{}\n", alloc == Allocator<int>{});
}