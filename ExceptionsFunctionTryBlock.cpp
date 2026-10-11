#include "common.hpp"

#include <exception>

void willThrow() try {
  throw std::runtime_error{"ERROR MSG"};
} catch (const std::exception& e) {
  std::print("Got exception with msg: {}\n", e.what());
}

int main() {
  willThrow();
}