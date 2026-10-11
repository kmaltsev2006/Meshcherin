/**
 * Dtors are nothrow by default
 * Using conditional noexcept you can make it opposite
 */

#include "common.hpp"

class Bad {
public:
  ~Bad() noexcept(false) try {
    throw std::runtime_error{"I am from Bad::~Bad()"};
  } catch (const std::exception& e) {
    std::print("Something went wrong during Bad object destruction, got exception\n");
  } // exception is implicitly thrown forward after catch

private:
  char* _data{nullptr};
};

int main() {
  try {
    Bad{};
  } catch (const std::exception& e) {
    std::print("Got exception in main: \"{}\"\n", e.what());
  }
}