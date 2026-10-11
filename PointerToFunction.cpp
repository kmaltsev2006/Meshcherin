#include "common.hpp"

bool cmp(const int a, const int b) { return a < b; }

int main() {
    bool (*cmp_ptr)(const int, const int) = nullptr;
    cmp_ptr = cmp;
    std::cout << std::boolalpha << cmp_ptr(10, 20) << std::noboolalpha
              << std::endl;
}