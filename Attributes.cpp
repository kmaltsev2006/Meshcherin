#include "common.hpp"

struct Empty {};

struct FakeEBO {
  template<typename T>
  [[deprecated]] [[nodiscard]] static int foo(int x, [[maybe_unused]] T param) {
    
    [[assume(x > 0)]];

    if (x > 0) [[likely]] {
      return -x;
    } else {
      return (-2) * x;
    }

  }

  int _filed;
  [[no_unique_address]] Empty _fake_field;
};

int main() {
  std::print("{}\n", sizeof(FakeEBO));
  std::print("{}\n", FakeEBO::foo<int>(42, 17));
  std::print("{}\n", FakeEBO::foo<int>(-42, 17));
}