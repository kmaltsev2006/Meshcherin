#include "common.hpp"

int main() {
  uint32_t* a = new uint32_t[4]{0};
  char* c = reinterpret_cast<char*>(a);
  ++c;

  uint32_t* b = reinterpret_cast<uint32_t*>(c);

  std::print("{} {} {}\n", static_cast<void*>(a), alignof(*a), std::bit_cast<uint64_t>(a) % alignof(*a));
  std::print("{} {} {}\n", static_cast<void*>(c), alignof(*c), std::bit_cast<uint64_t>(c) % alignof(*b));

  printBytes(*a, sizeof(*a) * 4);
  
  *b = 0xAA; // UB (+ maybe RE) (*b is not aligned to alignof(uint32_t))
  
  printBytes(*a, sizeof(*a) * 4);
  delete[] a;
}