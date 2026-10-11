#include "common.hpp"

struct EmptyBase {};
struct DerivedFromEmpty : EmptyBase {
    int d;
};

struct Base {
    char c;
};
struct Derived : Base {
    int d;
};

int main() {
    std::cout << "sizeof(EmptyBase) " << sizeof(EmptyBase) << std::endl;
    std::cout << "sizeof(DerivedFromEmpty) " << sizeof(DerivedFromEmpty)
              << std::endl;

    std::cout << "sizeof(Base) " << sizeof(Base) << std::endl;
    std::cout << "sizeof(Derived) " << sizeof(Derived) << std::endl;
}