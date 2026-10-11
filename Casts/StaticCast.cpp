/**
 * @brief static_cast<AnyType> - use "if you’re not sure you need another one"
 *
 * 1) conversions between compatible types
 * 2) conversions between void* and T*
 * 3) conversions in one class hierarchy
 */

#include "../common.hpp"

namespace my {
void* malloc(size_t sz) { return std::malloc(sz); }

void free(void* ptr) { std::free(ptr); }
} // namespace my

struct Base {
    Base() { PRINT_CALL(); }

    Base(const Base&) { PRINT_CALL(); }
    Base& operator=(const Base&) {
        PRINT_CALL();
        return *this;
    }

    void foo() { PRINT_CALL(); }
};
struct Derived : Base {
    void foo() { PRINT_CALL(); }
};

/*
 G
/ \
M D
\/
S
*/
struct Granny {
    void goo() { PRINT_CALL(); }
};
struct Mom : virtual Granny {
    void moo() { PRINT_CALL(); }
};
struct Dad : virtual Granny {
    void doo() { PRINT_CALL(); }
};
struct Son : Mom, Dad {
    void soo() { PRINT_CALL(); }
};

int main() {
    {
        auto x = static_cast<int64_t>(
            int32_t{42}); // ETI (explicitly typed initialization)
    }

    {
        char* ptr = static_cast<char*>(my::malloc(16));
        my::free(ptr);
    }

    {
        Derived d;
        d.foo();
        static_cast<Base&>(d).foo();
        static_cast<Base>(d).foo(); // slicing: new object created via copy ctor
    }

    {
        Dad* D = new Son{};
        static_cast<Son*>(D)->soo();

        delete static_cast<Son*>(D);
    }

    {
        Mom* M = new Son{};
        static_cast<Dad*>(static_cast<Son*>(M))->doo();

        delete static_cast<Son*>(M);
    }
}