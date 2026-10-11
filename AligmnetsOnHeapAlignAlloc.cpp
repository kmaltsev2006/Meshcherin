#include "common.hpp"

int main() {
  constexpr size_t alignment {32};
  void* ptr = std::aligned_alloc(alignment, 1); // address aligned to alignment
  // void* ptr = std::malloc(1); // address aligned to alignof(std::max_align_t_t) == 16

  std::print("{}\n", ptr);
  for (size_t i=2; i<=128; i*=2) {
    std::print("% {} == {}\n", i, std::bit_cast<uint64_t>(ptr) % i);
  }

  free(ptr);
}