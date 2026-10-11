#include "common.hpp"

template<typename T>
struct Base {
  int x {42};
};

template<>
struct Base<bool> {};

template<typename T>
struct Derived : Base<T> {
  void foo() {
    // std::print("{}", x);          // error: ‘x’ was not declared in this scope
    std::print("{}\n", this->x);     // OK
    std::print("{}\n", Base<T>::x);  // OK
  }
};

int main() {
  Derived<int> d;
  d.foo();

  Derived<bool> d2;
  // d2.foo(); // CE (has no member named ‘x’ & ‘x’ is not a member of ‘Base<bool>’)
}