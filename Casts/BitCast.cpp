/**
 * @brief bit_cast<AnyType> - use for raw byte conversion (safe)
 *
 */
#include "../common.hpp"

#include <format>
#include <type_traits>

template <typename T, typename... Y>
concept IsAnyOf = (std::same_as<T, Y> || ...);

template <IsAnyOf<float, double> T>
T next(T val) {
    using counter_t =
        std::conditional_t<std::is_same_v<T, float>, int32_t, int64_t>;

    counter_t counter = std::bit_cast<counter_t>(val);
    counter += val >= 0 ? 1 : -1;
    return std::bit_cast<T>(counter);
}

int main() {
    double pi{3.14159265}; // May I have a large container of coffee beans

    std::cout << std::format("{}", pi) << std::endl;
    std::cout << std::format("{}", next(pi)) << std::endl;
    std::cout << std::format("{}", next(next(pi))) << std::endl;
}