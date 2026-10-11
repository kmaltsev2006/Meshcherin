#include "common.hpp"

#include <utility>

struct Granny {
    Granny() = default;
    Granny(const Granny& rhs) { PRINT_CALL(); }
    Granny(Granny&& rhs) { PRINT_CALL(); }
};

struct Mom : Granny {
    Mom() = default;
    Mom(const Mom& rhs) : Granny{rhs} { PRINT_CALL(); }
    Mom(Mom&& rhs) : Granny{std::move(rhs)} { PRINT_CALL(); }
};

struct Son : Mom {
    Son() = default;
    Son(const Son& rhs) : Mom{rhs}, x{rhs.x} { PRINT_CALL(); }
    Son(Son&& rhs) : Mom{std::move(rhs)}, x{std::exchange(rhs.x, decltype(x){})} { PRINT_CALL(); }

    int x {42};
};

int main() {
    Son s0;

    Son s1 {s0};

    std::cout << std::endl;    
    
    Son s2 {std::move(s1)};
}