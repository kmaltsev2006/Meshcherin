#include "common.hpp"

class A {
public:
    void foo() { PRINT_CALL(); bar(); }
private:
    void bar() { PRINT_CALL(); }
protected:
    void baz() { PRINT_CALL(); }
};

class B : public A {
public:
    void soos() {
        foo();
        // bar(); // error: ‘void A::bar()’ is private within this context
        baz();
    }
};

int main() {
    A a;
    a.foo();
    // a.bar(); // error: ‘void A::bar()’ is private within this context
    // a.baz(); // error: ‘void A::baz()’ is protected within this context
}