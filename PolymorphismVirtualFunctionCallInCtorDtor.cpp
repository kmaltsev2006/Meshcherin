/**
 * @brief polymorphism mehanism "turn offs" when object is being created or destroyed
 * 
 * In reallity vptr dynamically updates during this process.
 *
 * Lets take a look what happens when Derived is being created:
 * 1) Base::Base() is called
 * 2) Base::vptr sets to 0x200 for example
 * 3) Calling foo leads to dereference of Base::vptr and calling Base::foo which is lying at Base vtable at 0x200
 * 4) Derived::Derived() is called
 * 5) Derived::Base::vptr is updated to 0x400 for example, only now it points to Derived vtable at 0x400,
 *    where overrided Derived::foo is lying
 * 
 * Process of destruction happens backwards
 *
 * Key words: construct_vtable, table of vtable of vtables (VTOVT)
 */

#include "common.hpp"

struct Base {
// static void* vptr;

    Base() {
        foo(); // Base::foo called
    }

    ~Base() {
        foo(); // Base::foo called
    }

    virtual void foo() {
        PRINT_CALL();
    }

};

struct Derived : Base {
// static void* Base::vptr;
    Derived() {}

    void foo() override {
        PRINT_CALL();
    }
};

int main() {
    Derived d;
}