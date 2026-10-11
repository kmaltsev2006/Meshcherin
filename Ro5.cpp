#include "common.hpp"

class A {
    A() = default;

    ~A() = default;
    A(const A&) = default;
    A& operator=(const A&) = default;
    A(A&&) = default;
    A& operator=(A&&) = default;
};

int main() {}