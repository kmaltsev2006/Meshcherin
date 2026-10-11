#include "common.hpp"

class Base {
public:
    explicit Base(int) { PRINT_CALL(); }
    explicit Base(bool) { PRINT_CALL(); }
    explicit Base(double, double) { PRINT_CALL(); }
};

class Derived : public Base {
using Base::Base; // Base Ctors are now avaliable for derived (but CopyCtor and MoveCtor are still not inherited!)
};

int main() {
    Derived d{double{}, double{}};
}