/**
 * After exception is thrown all local variables dtor-s are called
 */
#include "common.hpp"

#include <memory>

void willThrowUB() {
  char* ptr = new char{};
  
  throw 42;

  delete ptr;
}

void willThrow() {
  std::unique_ptr<char> u_ptr = std::make_unique<char>();

  throw 42;
}

int main() {
  try {
    willThrowUB(); // memory leak, bc ptr is destroyed, but memory not cleared
  } catch(...) {}

  try {
    willThrow();   // OK
  } catch(...) {}
}