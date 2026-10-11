#include "common.hpp"

#include <unordered_map>

using my_t = int;

template <typename Key, typename T>
using u_map = std::unordered_map<Key, T>;

namespace a {
namespace b {
void foo() {}
} // namespace b
} // namespace a

int main() {
    { u_map<my_t, my_t> m; }

    {
        using a::b::foo;
        foo();
    }

    {
        using namespace a;
        b::foo();
    }
}