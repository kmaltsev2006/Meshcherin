/**
 * BTW: operator new, operator delete, operator new[], operator delete[] methods
 * are implicitly static
 */

#include "common.hpp"

void* operator new(size_t count) {
  PRINT_CALL();
  return malloc(count);
}

void operator delete(void* ptr) {
  free(ptr);
}

class MyClass {
public:
  static void* operator new(size_t count) {
    PRINT_CALL();
    return malloc(count);
  }

  static void operator delete(void* ptr) {
    free(ptr);
  }

};

int main() {
  {
    MyClass* ptr = new MyClass{};
    delete ptr;
  }

  {
    int* ptr = new int{};
    delete ptr;
  }
}