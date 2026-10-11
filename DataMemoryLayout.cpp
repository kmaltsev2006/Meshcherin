#include "common.hpp"

struct A {
    int x;
    char c;
};

int main() {
    std::cout << "sizeof(A::x) " << sizeof(A::x) << std::endl;
    std::cout << "sizeof(A::c) " << sizeof(A::c) << std::endl;
    std::cout << "sizeof(A) " << sizeof(A) << std::endl;
    std::cout << "alignof(A::x) " << alignof(A::x) << std::endl;
    std::cout << "alignof(A::c) " << alignof(A::c) << std::endl;
    std::cout << "alignof(A) " << alignof(A)
              << " == " << "std::max(alignof(A::x), alignof(A::c)) "
              << std::max(alignof(A::x), alignof(A::c)) << std::endl;
}