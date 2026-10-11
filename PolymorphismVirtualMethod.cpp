#include "common.hpp"

struct Base {
    uint64_t b {0xAA};
    virtual void foo() { PRINT_CALL(); }
};

struct Derived : Base {
    uint64_t d {0xBB};
    void foo() override final { PRINT_CALL(); }
}; // |40ED27D6.38560000|AA000000.00000000|BB000000.00000000|
//    |vbptr                     Base     -        Derived  |

int main() {
    printInfo<Derived>();
    Derived d;
    Base& br {d};
    br.foo(); // virtual void Derived::foo()
}