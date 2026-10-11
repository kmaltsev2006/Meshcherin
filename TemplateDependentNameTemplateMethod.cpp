/**
 * Unlike the previous example, here you cannot do without template keyword
 */
#include "common.hpp"

template<typename T>
struct S {
  template<typename Y>
  static void foo() { PRINT_CALL(); }
};

template<typename T, typename Y>
void bar() {
  S<T>::template foo<Y>();
}

int main() {
  bar<bool, int>();
}