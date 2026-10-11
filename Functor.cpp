#include "common.hpp"

#include <algorithm>
#include <vector>

namespace my {
struct less {
    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const noexcept {
        return lhs < rhs;
    }
};
} // namespace my

int main() {
    std::vector<int32_t> v = {3, 2, 1};
    std::sort(v.begin(), v.end(), my::less{});
    std::for_each(v.cbegin(), v.cend(),
                  [](const auto& el) { std::cout << el << " "; });
    std::cout << std::endl;
}