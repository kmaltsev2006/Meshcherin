/**
 * Compiler parses dependent name as expression by default
 * Use typename keyword to parse it as type
 */
#include "common.hpp"

template<typename T>
struct S {
  using smth = int32_t;
};

template<>
struct S<bool> {
  static const char smth {};
};

template<typename T>
void foo() {
  char q {S<T>::smth};
}

template<typename T>
void bar() {
  typename S<T>::smth q{};
}

int main() {
  // foo<int>(); // error: dependent-name ‘S<T>::smth’ is parsed as a non-type, but instantiation yields a type
  foo<bool>();
  bar<int>();
  // bar<bool>(); // error: ‘typename S<bool>::smth’ names ‘char S<bool>::smth’, which is not a type
}