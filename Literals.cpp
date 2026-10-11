#include "common.hpp"

#include <numbers>

constexpr long double operator""_to_rad(const long double deg) {
    return std::numbers::pi_v<long double> / 180.0L * deg;
}

int main() {
    auto c = 'a';
    const auto text = "abc";
    auto d = 3.14;
    auto f = 3.14f;
    auto ui = 42u;
    auto ld = 60.0_to_rad;

    printTypeNoCE(c);
    printTypeNoCE(text);
    printTypeNoCE(d);
    printTypeNoCE(f);
    printTypeNoCE(ui);
    printTypeNoCE(ld);
}
