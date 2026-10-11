#include "common.hpp"

#include <type_traits>

template<typename T>
struct RemoveConst {
  using type = T;
};

template<typename T>
struct RemoveConst<const T> {
  using type = T;
};

template<typename T>
using RemoveConst_t = typename RemoveConst<T>::type;


int main() {
  int value {42};

  const int ci {value};
  int* const cptr {&value};
  const int& cref {value};

  RemoveConst_t<decltype(ci)> i {ci};
  RemoveConst_t<decltype(cptr)> ptr {cptr};
  RemoveConst_t<decltype(cref)> ref {cref};

  // printTypeCE<decltype(ci)>(); // error: use of deleted function ‘void printTypeCE() [with T = const int]’
  // printTypeCE<decltype(i)>(); // error: use of deleted function ‘void printTypeCE() [with T = int]’

  // printTypeCE<decltype(cptr)>(); // error: use of deleted function ‘void printTypeCE() [with T = int* const]’
  // printTypeCE<decltype(ptr)>(); // error: use of deleted function ‘void printTypeCE() [with T = int*]’
  
  // printTypeCE<decltype(cref)>(); // error: use of deleted function ‘void printTypeCE() [with T = const int&]’
  // printTypeCE<decltype(ref)>(); // error: use of deleted function ‘void printTypeCE() [with T = const int&]’
}