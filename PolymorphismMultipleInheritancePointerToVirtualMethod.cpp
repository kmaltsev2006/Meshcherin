#include "common.hpp"

struct Mom {
    virtual void foo() { PRINT_CALL(); }
};
struct Dad {
    virtual void bar() { PRINT_CALL(); }
};
struct Son : Mom, Dad {
    void foo() override { PRINT_CALL(); }
    void bar() override { PRINT_CALL(); }
};

struct PointerToMember {
    uint64_t ptr;
    uint64_t offset;
};

int main() {
    void (Son::* p_foo)() = &Son::foo;
    void (Son::* p_bar)() = &Son::bar;

    std::cout << std::bit_cast<PointerToMember>(p_foo).ptr << std::endl; // 1
    std::cout << std::bit_cast<PointerToMember>(p_bar).ptr << std::endl; // 9
    /*
    | &Son::foo | &Son::bar |
    |     8     |     8     |

    1 == 0 | 1
    9 == 8 | 1
    */

    Son s;
    (s.*(&Mom::foo))(); // polymorphism still works
    (s.*(&Dad::bar))(); // polymorphism still works
}