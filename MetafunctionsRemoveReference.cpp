#include "common.hpp"

template<typename T>
struct RemoveReference {
  using type = T;
};

template<typename T>
struct RemoveReference<T&> {
  using type = T;
};

template<typename T>
struct RemoveReference<T&&> {
  using type = T;
};

template<typename T>
using RemoveReference_t = typename RemoveReference<T>::type;

int main() {
  int x {42};
  int& rx {x};

  RemoveReference_t<decltype(rx)> y {rx};

  // printTypeCE<decltype(rx)>(); // error: use of deleted function ‘void printTypeCE() [with T = int&]’
  // printTypeCE<decltype(y)>();  // error: use of deleted function ‘void printTypeCE() [with T = int]’

  x = 17;
  std::print("x = {}; rx = {}; y = {}\n", x, rx, y);
}