/**
 * @brief operator comma evaluates expressions from left to right and return the result of last one
 * 
 */
#include "common.hpp"

int foo() {PRINT_CALL(); return 0;}
int bar() {PRINT_CALL(); return 17;}
int baz() {PRINT_CALL(); return 42;}

int main() {
  int x = (foo(), bar(), baz());
  std::print("x = {}\n", x);
}