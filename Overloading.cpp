#include "common.hpp"

void foo(int) { PRINT_CALL(); }

void foo(double) { PRINT_CALL(); }

int main() {
    foo(int{});
    foo(double{});

    // Promotion > Conversion > User defined conversion
    foo(float{}); // Promotion to double

    // Narrowing conversion
    // foo(double{}); // error: call of overloaded ‘foo(double)’ is ambiguous
}