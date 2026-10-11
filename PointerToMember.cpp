#include "common.hpp"

#include <cstdint>
#include <cstring>

class A {
  public:
    void foo() {
        PRINT_CALL();
        std::cout << x << std::endl;
    }

    int x{42};
};

struct PtrToMember {
    uintptr_t ptr;
    uintptr_t offset;
};

int main() {
    A a;

    int A::*A_x_ptr = &A::x;
    std::cout << sizeof(A_x_ptr) << std::endl;
    std::cout << "a.x: " << a.*A_x_ptr << std::endl;

    std::cout << std::endl;

    void (A::*A_foo_ptr)() = &A::foo;
    std::cout << sizeof(A_foo_ptr) << std::endl;

    std::cout << "Raw ptr: " << reinterpret_cast<void*>(A_foo_ptr) << std::endl;
    std::cout << "Ptr: " << std::hex
              << std::bit_cast<PtrToMember*>(&A_foo_ptr)->ptr << std::dec
              << std::endl;
    std::cout << "Offset: " << std::hex
              << std::bit_cast<PtrToMember*>(&A_foo_ptr)->offset << std::dec
              << std::endl;

    (a.*A_foo_ptr)();
}