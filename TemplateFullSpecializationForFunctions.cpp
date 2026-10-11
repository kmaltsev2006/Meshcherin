/**
 * 1) template overload resolution
 * 2) specification overload resolution
 */
#include "common.hpp"

// OVERLOAD 1
template<typename T, typename Y>
void foo() {
  std::print("1\n");
}

template<>
void foo<int, int>() {
  std::print("2\n");
}

// OVERLOAD 2
template<typename T, typename Y>
void foo(T, Y) {
  std::print("3\n");
}

template<>
void foo(bool, bool) {
  std::print("4\n");
}

template<>
void foo(int, int) {
  std::print("5\n");
}

// OVERLOAD 3
template<typename T>
void foo(T, T) {
  std::print("6\n");
}

template<>
void foo(bool, bool) {
  std::print("7\n");
}

int main() {
  foo<bool, bool>();   // OVERLOAD 1 -> 1
  foo<int, int>();     // OVERLOAD 1 -> 2
  foo(bool{}, bool{}); // OVERLOAD 3 -> 7
}