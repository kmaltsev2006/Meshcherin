#include "common.hpp"

#include <type_traits>

enum class Rgb : size_t {
    kRed,
    kGreen,
    kBlue,
};

template <typename E>
constexpr auto eId(const E& e) {
    return static_cast<std::underlying_type_t<E>>(e);
}

int main() { std::cout << eId(Rgb::kBlue) << std::endl; }