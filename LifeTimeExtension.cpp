#include "common.hpp"

struct A {
    A() { PRINT_CALL(); }
    ~A() { PRINT_CALL(); }

    void foo() const { PRINT_CALL(); }
};

int main() {
    {
        const A& a_ref{A{}}; // Not dangling reference

        std::cout << "A obj is still alive" << std::endl;
        a_ref.foo();
        std::cout << "A obj is still alive" << std::endl;
    }
    std::cout << "A obj is destroyed" << std::endl;
}