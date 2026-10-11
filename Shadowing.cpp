#include "common.hpp"

int main() {
    int x{42};
    {
        int x{17}; // shadows x from bigger scope
        std::cout << x << std::endl;
    }
}