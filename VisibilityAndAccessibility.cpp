#include "common.hpp"

struct Base {
void foo(double) { PRINT_CALL(); }
};

struct Derived : Base {
void foo(int) { PRINT_CALL(); } // shadows Base::foo(double)
};

int main() {
    Derived d;
    d.foo(3.14); // double implicitly casts to int and Derived::foo(int) called  
    d.Base::foo(3.14);
}