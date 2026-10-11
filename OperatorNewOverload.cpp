/**
 * operator new and operator new[] return pointer aligned to alignof(std::max_align_t)
 */
#include "common.hpp"

struct LifeTime {
  LifeTime() { PRINT_CALL(); }
  LifeTime(const LifeTime& rhs) { PRINT_CALL(); }
  LifeTime(LifeTime&& rhs) { PRINT_CALL(); }
  ~LifeTime() { PRINT_CALL(); }
};

void* operator new(size_t count) {
  // new must allocate at least 1 byte
  if (count == 0)
    count = 1;

  std::print("Bytes allocated: {}\n", count);
  void* ptr = malloc(count);
  if (!ptr) {
    throw std::bad_alloc{};
  }
  return ptr;
}

void operator delete(void* ptr) {
  std::print("Deallocated\n");
  free(ptr);
}

void* operator new[](size_t count) {
  std::print("[] Bytes allocated: {}\n", count);
  return operator new(count);
}

void operator delete[](void* ptr) {
  operator delete(ptr);
}

int main() {
  {
    LifeTime* lt = new LifeTime{}; // operator new(...) -> new(ptr) LifeTime{}
    delete lt;                     // ptr->~LifeTime() -> opeator delete(ptr) 
  }

  std::print("\n");

  {
    // 18 bytes allocated, not 10, because type is non-trivial
    LifeTime* lt_arr = new LifeTime[10]{};  // opeator new[](...+8) -> operator new(...+8) -> for i in ... {new(ptr + i) LifeTime{}}
    size_t sz = *reinterpret_cast<size_t*>(reinterpret_cast<std::byte*>(lt_arr) - 8);
    std::print("Size: {}\n", sz);
    delete[] lt_arr;                        // for i in ... {(8 + ptr + i)->~LifeTime()} -> operator delete[]() -> operator delete()
  }

  std::print("\n");

  { 
    // 40 bytes allocated, not 48, because type is trivial
    int* int_arr = new int[10]{};
    delete[] int_arr;
  }
}