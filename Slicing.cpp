#include "common.hpp"

struct Base {
    Base() { PRINT_CALL(); }
    ~Base() { PRINT_CALL(); }
    Base(const Base&) { PRINT_CALL(); }
    Base(Base&&) { PRINT_CALL(); }


    int x {};
    int y {};   
};

struct Derived : Base {
    Derived() { PRINT_CALL(); }
    ~Derived() { PRINT_CALL(); }
    Derived(const Derived&) { PRINT_CALL(); }
    Derived(Derived&&) { PRINT_CALL(); }

    int z {};
};

void foo(Base) {}

int main() {
    Derived d;
    foo(d); // implicit cast Derived& -> Base&; Base::Base(const Base&) called
}