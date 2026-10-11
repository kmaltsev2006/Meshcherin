#include "common.hpp"

template <typename T>
T& getValRef() {
    T val{};
    return val; // UB
}

int main() {
    auto& val_ref = getValRef<int32_t>();
    val_ref = 42; // Segmentation fault (core dumped)
}