#include "common.hpp"

void foo() {}

int main() {
    int x{};
    int& y = x;
    int& z = y;

    /*

    y  z
     \/
     x

    */
}