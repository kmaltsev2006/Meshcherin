/**
 * Depricated since g++11:
 * Dependent name parsed as type when used typename keyword, but not as template
 * Use template keyword to parse it as template
 */
#include "common.hpp"

#include <array>

template<typename T>
struct Special {
  template<size_t N>
  using Array = std::array<T, N>;
};

template<typename T, size_t N>
auto genSpecialArrayDepricated() {
  return typename Special<T>::template Array<N>{}; // depricated
}

template<typename T, size_t N>
auto genSpecialArrayModern() {
  return typename Special<T>::Array<N>{}; // since g++11
}

int main() {
  genSpecialArrayDepricated<int, 42>();
  genSpecialArrayModern<int, 42>();
}