#include "common.hpp"

#include <cstdarg>

namespace my {

template <typename T>
T sum(size_t count, ...) {
    std::va_list args;
    va_start(args, count);

    T sm{};
    for (size_t i = 0; i < count; ++i) {
        sm += va_arg(args, T);
    }

    va_end(args);
    return sm;
}

void printf(size_t sz, bool some_random_flag, bool one_more_random_flag, ...) {
    std::va_list args;
    va_start(args, one_more_random_flag);

    for (size_t i = 0; i < sz; ++i) {
        std::cout << va_arg(args, const char*) << " ";
    }
    std::cout << std::endl;

    va_end(args);
}

} // namespace my

int main() {
    std::cout << my::sum<int32_t>(5, 1, 2, 3, 4, 5) << std::endl;
    my::printf(5, bool{}, bool{}, "Hello!", "I", "am", "variadic", "function.");
}