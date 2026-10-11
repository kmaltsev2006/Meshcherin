#include "common.hpp"

template<size_t N>
struct Fibonacci {
  static constexpr size_t value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template<>
struct Fibonacci<1> {
  static constexpr size_t value = 1;
};

template<>
struct Fibonacci<0> {
  static constexpr size_t value = 0;
};

template<size_t N>
constexpr size_t kFibonacci_v = Fibonacci<N>::value;

int main() {
  std::print("{} {} {} {} {} {} {} {} {} {}\n",
    kFibonacci_v<0>, kFibonacci_v<1>, kFibonacci_v<2>, kFibonacci_v<3>, kFibonacci_v<4>,
    kFibonacci_v<5>, kFibonacci_v<6>, kFibonacci_v<7>, kFibonacci_v<8>, kFibonacci_v<9>);

  // std::print("{}\n", kFibonacci_v<1000>) // fatal error: template instantiation depth exceeds maximum of 900
}