#include "common.hpp"

#include <type_traits>

template<typename... Ts>
struct IsAllSame {};

template<typename First, typename Second, typename Third, typename... Ts>
struct IsAllSame<First, Second, Third, Ts...> {
  static constexpr bool value = IsAllSame<First, Second>::value &&
                                IsAllSame<Second, Third>::value &&
                                IsAllSame<Third, Ts...>::value;
};

template<typename First, typename Second>
struct IsAllSame<First, Second> {
  static constexpr bool value = std::is_same_v<First, Second>;
};

template<typename First>
struct IsAllSame<First> {
  static constexpr bool value = true;
};

template<typename... Ts>
constexpr bool IsAllSame_v = IsAllSame<Ts...>::value;

int main() {
  std::print("{}\n", IsAllSame_v<int>);
  std::print("{}\n", IsAllSame_v<int, bool>);
  std::print("{}\n", IsAllSame_v<int, int, int>);
  std::print("{}\n", IsAllSame_v<int, int, int, bool>);
  std::print("{}\n", IsAllSame_v<int, int, int, int, int>);
  std::print("{}\n", IsAllSame_v<int, int, int, int, int, bool>);
}