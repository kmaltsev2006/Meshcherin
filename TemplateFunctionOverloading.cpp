#include "common.hpp"

void foo(int) {
  PRINT_CALL();
}

template<typename T>
void foo(T) {
  PRINT_CALL();
}

int main() {
  foo(int{});  // non-template version called
  foo(char{}); // template version called
}