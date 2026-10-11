#include "common.hpp"

int main() {
    int x{42};

    {
        const int* x_ptr = &x;
        *x_ptr = 17;     // CE
        x_ptr = nullptr; // OK
    }

    {
        int* const x_ptr = &x;
        *x_ptr = 17;     // OK
        x_ptr = nullptr; // CE
    }

    {
        const int* const x_ptr = &x;
        *x_ptr = 17;     // CE
        x_ptr = nullptr; // CE
    }
}