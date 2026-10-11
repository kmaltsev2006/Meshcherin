#include "common.hpp"

void print() {
  std::cout << std::endl;
}

template<typename T, typename... Ts>
void print(const T& head, const Ts&... args) {
  std::cout << head << " ";
  print(args...);
}

int main() {
  print('a', 10, 20, "thirty", 42);
}