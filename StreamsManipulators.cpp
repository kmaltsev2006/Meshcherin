/**
 * Streams manipulators works like this:
 *
  std::ios_base& operator<<(std::ios_base& ios, std::ios_base& (*func)(std::ios_base&)) {
    func(ios);
    return ios;
  }
 */
#include "common.hpp"

int main() {
  std::cout << true << std::endl;
  std::cout << std::boolalpha << true << std::noboolalpha << std::endl;
  printTypeNoCE(std::boolalpha); // std::ios_base& (*)(std::ios_base&)
}