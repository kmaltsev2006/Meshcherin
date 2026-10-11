#include "common.hpp"

template<typename T, typename F, bool exp>
struct Conditional {};

template<typename T, typename F>
struct Conditional<T, F, true> {
  using type = T;
};

template<typename T, typename F>
struct Conditional<T, F, false> {
  using type = F;
};

template<typename T, typename F, bool exp>
using Conditional_t = typename Conditional<T, F, exp>::type;

int main() {
  {
    Conditional_t<int, char, (10 < 20)> var {};
    printTypeNoCE(var);
  }

  {
    Conditional_t<int, char, (10 > 20)> var {};
    printTypeNoCE(var);
  }  
}