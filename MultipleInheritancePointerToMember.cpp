#include "common.hpp"

#include <iomanip>

struct Mom {
    uint64_t m {0xAA};
    void foo() { PRINT_CALL(); }
};

struct Dad {
    uint64_t d {0xBB};
    void bar() { PRINT_CALL(); }
};

struct Son : Mom, Dad {
    uint64_t s {0xCC};
    void foo() { PRINT_CALL(); }
    void bar() { PRINT_CALL(); }
};

struct PointerToMember {
    uint64_t ptr;
    uint64_t offset;
};

int main() {
    printInfo<Son>();

    void (Mom::* m_ptr_foo)() = &Mom::foo;
    void (Son::* s_ptr_foo)() = m_ptr_foo;

    void (Dad::* d_ptr_bar)() = &Dad::bar;
    void (Son::* s_ptr_bar)() = d_ptr_bar;

    std::cout << std::bit_cast<PointerToMember>(m_ptr_foo).offset << std::endl; // 0
    std::cout << std::bit_cast<PointerToMember>(s_ptr_bar).offset << std::endl; // 8

    Son s;
    (s.*s_ptr_foo)(); // Mom::foo() called
    (s.*s_ptr_bar)(); // Dad::foo() called
    s.foo(); // Son::foo() called
    s.bar(); // Son::bar() called
}