#include "common.hpp"

template<typename T>
class MyClass {
public:
  MyClass() {
    std::print("Impl1 invoked\n");
  }
};

template<>
class MyClass<int> {
public:
  MyClass() {
    std::print("Impl2 invoked\n");
  }
};

template<>
class MyClass<char> {
public:
  MyClass() {
    std::print("Impl3 invoked\n");
  }
  
  void foo() {}
};

int main() {
  MyClass<bool>{}; // 1
  MyClass<long>{}; // 1
  MyClass<int>{};  // 2
  MyClass<char>{}; // 3

  // MyClass<bool>{}.foo(); // 1 // error: ‘class MyClass<bool>’ has no member named ‘foo’
}