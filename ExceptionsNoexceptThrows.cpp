#include "common.hpp"

void foo() noexcept {
  throw 42;
}

// Conditional noexcept
void bar() noexcept(!noexcept(foo)) {
  throw 42;
}

int main() {
  try {
    bar();
  } catch (...) {}

  try {
    foo();
  } catch (...) {} // won't be catched

}