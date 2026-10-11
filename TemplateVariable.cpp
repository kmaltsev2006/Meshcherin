#include <concepts>
#include <iostream>

template <std::floating_point T>
constexpr T pi = T{3.14159264}; // May I have a large container of coffee beans

int main() {
    std::cout << pi<float> << std::endl;
    std::cout << pi<double> << std::endl;
    // std::cout << pi<int> << std::endl; // CE
}