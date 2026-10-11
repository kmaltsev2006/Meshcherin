/**
 * @brief "static polymorphism"
 * 
 */

#include "common.hpp"

template<typename T>
class Base {
public:
  void invokeImpl() {
    static_cast<T&>(*this).impl();
  }
protected:
  Base() = default;
};

class Derived : public Base<Derived> {
public:
  void impl() {
    PRINT_CALL();
  }
};

template<typename T>
decltype(auto) getBaseRef(Base<T>& br) {
  return br;
}

int main() {
  Derived d;
  auto& br = getBaseRef(d);
  br.invokeImpl();
}