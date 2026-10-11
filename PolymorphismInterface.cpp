#include "common.hpp"

struct Interface {
public:
    virtual void foo() const = 0;
};

struct Impl1 : Interface {
    void foo() const override {
        PRINT_CALL();
    }
};

struct Impl2 : Interface {
    void foo() const override {
        PRINT_CALL();
    }
};

bool checkIfImpl2(Interface* i) {
    return !dynamic_cast<Impl2*>(i);
}

int main() {
    Interface* i1 = new Impl1 {};
    Interface* i2 = new Impl2 {};

    std::cout << "i1 is impl2: " << std::boolalpha << checkIfImpl2(i1) << std::noboolalpha << std::endl;
    std::cout << "i2 is impl2: " << std::boolalpha << checkIfImpl2(i2) << std::noboolalpha << std::endl;

    i1->foo();
    i2->foo();
    
    delete i1;
    delete i2;
}