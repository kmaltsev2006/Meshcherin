#include "common.hpp"

void foo();

void bar() { foo(); }

void foo() { bar(); }

int main() {}