#include "common.hpp"

struct Granny {
    Granny() { PRINT_CALL(); }
    ~Granny() { PRINT_CALL(); }
};

struct Mom : Granny {
    Mom() /*: Granny() implicitly called*/ { PRINT_CALL(); }
    ~Mom() { PRINT_CALL(); }
};

struct Son : Mom {
    Son() /*: Mom() implicitly called*/ { PRINT_CALL(); }
    ~Son() { PRINT_CALL(); }
};

int main() {
    Son s;
}