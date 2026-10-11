#include "common.hpp"

#include <utility>

void bar() {}

template<typename T, typename X, typename Y, typename Z>
void bar(T, X, Y, Z) {}

template<typename... Ts>
void foo(Ts&&... args) {
  std::print("{}\n", sizeof...(args));
  std::print("{}\n", sizeof...(Ts));

  bar(args...);                    // pass by value
  bar(std::forward<Ts>(args)...);  // perfect forwarding
}

int main() {
  int x {42};
  
  foo(10, 20, 30, x);

  foo();

  // foo(1, 2, 3); // error: no matching function for call to ‘bar(int&, int&, int&)’
}