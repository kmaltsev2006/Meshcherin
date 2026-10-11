#include "common.hpp"

template<typename T, typename Y>
struct isSame {
  static constexpr bool value = false;
};

template<typename T>
struct isSame<T, T> {
  static constexpr bool value = true;
};

template<typename T, typename Y>
constexpr bool isSame_v = isSame<T, Y>::value;

int main() {
  std::print("{}\n", isSame_v<int, int>);
  std::print("{}\n", isSame_v<int, bool>);
}