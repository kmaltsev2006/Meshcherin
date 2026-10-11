/**
 * 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
 * 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)
 */
#include "common.hpp"

// I: std::cout
// op: <<
// E: args
template<typename... Ts>
void print(const Ts&... args) {
  (std::cout << ... << args) << std::endl;
}

// op: ,
// E: (std::cout << args << delim)
template<typename... Ts>
void printWithDelimiter(char delim, const Ts&... args) {
  ((std::cout << args << delim), ...) << std::endl;
}

int main() {
  print('a', 10, 20, "thirty", 42);
  printWithDelimiter(' ', 'a', 10, 20, "thirty", 42);
}