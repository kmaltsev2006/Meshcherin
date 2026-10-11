#include "common.hpp"

int main() {
    int* x;
    (char*)x;   // OK
    (double*)x; // UB
}