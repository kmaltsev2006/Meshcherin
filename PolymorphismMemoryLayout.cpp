#include "common.hpp"

struct Base {
// static void* bvptr;
    uint64_t a {0xAA};
    virtual ~Base() = default;
}; // |182DB8FF.9C570000|AA000000.00000000|

struct Derived : Base {
// static void* Base::bvptr; (Derived uses Base vptr as his own, but with different value)
    uint64_t b {0xBB};
}; // |F82CB8FF.9C570000|AA000000.00000000|BB000000.00000000|

int main() {
    printInfo<Base>();
    printInfo<Derived>();
}