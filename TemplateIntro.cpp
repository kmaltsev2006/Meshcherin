#include "common.hpp"

#include <utility>
#include <vector>
#include <type_traits>

template<typename T>
void swap(T& a, T& b) {
  T tmp {std::move(a)};
  a = std::move(b);
  b = std::move(tmp);
}

template<typename T, typename Y=bool>
struct S {
  T t {};
  Y y {};
};

template<typename T>
using Vector = std::vector<T>;

template<std::floating_point T>
constexpr T kPi = static_cast<T>(3.14159264);

// Id for typename can be ommited
template<typename>
void foo() { PRINT_CALL(); };

template<typename...>
void bar() { PRINT_CALL(); };

int main() {
  S<char> a;
  S<char, bool> b;
  Vector<S<char, bool>> v {std::move(a), std::move(b)};
  swap(v[0], v[1]);

  foo<int>();
  bar<>();
  bar<int, char, bool>();

  std::print("PI: {}\n", kPi<float>);
}