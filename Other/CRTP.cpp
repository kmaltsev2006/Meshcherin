/**
 * @brief CRTP (Curiously Recurring Template Pattern)
 *
 */
#include <concepts>
#include <iostream>
#include <type_traits>

template <typename D>
class Base {
  public:
    void invokeImpl() { static_cast<D&>(*this).impl(); }

    static void invokeStaticImpl() { D::staticImpl(); }

  protected:
    Base() = default;
};

class Derived_1 : public Base<Derived_1> {
  public:
    Derived_1() = default;

    void impl() { std::cout << "Derived 1" << std::endl; }
};

class Derived_2 : public Base<Derived_2> {
  public:
    Derived_2() = default;

    void impl() { std::cout << "Derived 2" << std::endl; }
};

class Q {
    void invokeImpl() {}
};

template <typename T>
concept IsDerivedFromBase =
    std::derived_from<std::decay_t<T>, Base<std::decay_t<T>>>;

void process(IsDerivedFromBase auto&& b) { b.invokeImpl(); }

int main() {
    Derived_1 d_1{};
    process(d_1);
    process(Derived_2{});
    // process(Q{}); // CE
}