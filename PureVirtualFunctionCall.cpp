/**
 * @brief Happens bc of mechanism explained in `PolymorphismVirtualFunctionCallInCtorDtor.cpp`
 * 
 * Pure virtual function is "quite real" and it looks like something like that:
 *
    virtual void foo() = 0;

    void foo() {
        std::cerr << "pure virtual method called" << std::endl;
        std::terminate();
    }
 *
 */

#include "common.hpp"

struct Base {
    virtual void foo() = 0;

    void bar() { foo(); }

    // if foo will be called directly ld error happens
    Base() { bar(); }
    ~Base() { bar(); }
};

struct Derived : Base {
    void foo() override {
        PRINT_CALL();
    }
};

int main() {
    Derived d;
    // pure virtual method called
    // terminate called without an active exception
}