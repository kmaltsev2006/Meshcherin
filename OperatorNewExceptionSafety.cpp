#include "common.hpp"

#include <utility>

struct FirstTag {};
struct SecondTag {};
struct ThirdTag {};

struct Bad {
  Bad() { throw 42; }
  ~Bad() { PRINT_CALL(); }
};

struct PendingBad {
  PendingBad() { if (id > 3) throw 42; ++id; }
  ~PendingBad() { PRINT_CALL(); }
  static size_t id;
};
size_t PendingBad::id{0};

void* operator new(size_t count, FirstTag) {
  PRINT_CALL();
  return malloc(count);
}

void* operator new(size_t count, SecondTag) {
  PRINT_CALL();
  return malloc(count);
}

void* operator new[](size_t count, ThirdTag tag) {
  PRINT_CALL();
  return operator new(count);
}

void operator delete(void* ptr, FirstTag) {
  PRINT_CALL();
  free(ptr);
}

void operator delete(void* ptr, SecondTag) {
  PRINT_CALL();
  free(ptr);
}

void operator delete[](void* ptr, ThirdTag tag) {
  PRINT_CALL();
  operator delete(ptr);
}

int main() {
  try {
    Bad* ptr = new(SecondTag{}) Bad{};
  } catch (...) {
    std::print("Caught\n");
  }

  std::print("\n");

  try {
    PendingBad* ptr = new(ThirdTag{}) PendingBad[10]{};
  } catch (...) {
    std::print("Caught\n");
  }
}