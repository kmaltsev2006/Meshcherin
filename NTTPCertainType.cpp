#include "common.hpp"

template<typename T, size_t N>
class Array {
private:
  T _data[N];
};

int main() {
  constexpr size_t size = 42;
  Array<int, size> arr;
}