#include "common.hpp"

void foo() {
  try {
    int x = 5 / 0; // CPU exception (RE) invoked: `Floating point exception (core dumped)`
  } catch(...) {}  // won't be catched
}

void bar() {
  try {
    throw 42;     // C++ exception invoked
  } catch(...) {} // will be catched
}

int main() {
  // foo(); // UB
  bar(); // OK
}