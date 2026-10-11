#include "common.hpp"

struct Mom {
    uint64_t m {};
};
struct Dad {
    uint64_t d {};
};
struct Son : Mom, Dad {
    uint64_t s {};
};

int main() {
    Son s;
    Dad& d {s};
    std::cout << "Son address: " << &s << std::endl;
    std::cout << "Dad address: " << &d << std::endl; // shifted by 8 to right
}