#include "common.hpp"

class Base {
public:
    void foo() { PRINT_CALL(); }
private:
    void bar() { PRINT_CALL(); }
protected:
    void baz() { PRINT_CALL(); }
};

class Derived : private Base {
public:
    void soos() {
        foo(); // OK
        // bar(); // error: ‘void Base::bar()’ is private within this context
        baz(); // OK
    }

/* Inheritance intuition:
private:                // access
    public:             // access
        Base::foo();
    private:            // no access
        Base::bar();
    protected:          // acces
        Base::baz();
*/
};

int main() {
    Derived d;
    // Base& br {static_cast<Base&>(d)}; // error: ‘Base’ is an inaccessible base of ‘Derived’
}