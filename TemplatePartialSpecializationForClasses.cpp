#include "common.hpp"

template<typename T, typename Y>
class MyClass {
public:
  MyClass() {
    std::print("Impl1 invoked\n");
  }
};

template<typename T>
class MyClass<T, bool> {
public:
  MyClass() {
    std::print("Impl2 invoked\n");
  }
};

int main() {
  MyClass<int, int>{};   // 1
  MyClass<int, bool>{};  // 2
  MyClass<char, bool>{}; // 2
}