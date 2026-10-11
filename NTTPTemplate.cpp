/**
 * The intuition is that we seem to be putting declaration of A inside the template of B and adding typename keyword:
 *
 * `template<typename, typename>`
 * A {...};
 *
 * template< `template<typename, typename>` typename A >
 * B {...};
 */

#include "common.hpp"

#include <vector>
#include <map>

// Non-variadic variant
template<typename T, template<typename> typename Container>
class BasicWrapper {
public:
  Container<T>& operator()() {
    return _container;
  }

private:
  Container<T> _container;
};

// Variadic variant
template<template<typename...> typename Container, typename... Ts>
class Wrapper {
public:
  Container<Ts...>& operator()() {
    return _container;
  }

private:
  Container<Ts...> _container;
};

int main() {
  BasicWrapper<int, std::vector> basic_wrapper;
  basic_wrapper().emplace_back(42);

  Wrapper<std::map, int, int> wrapper;
  wrapper().emplace(42, 17);
}