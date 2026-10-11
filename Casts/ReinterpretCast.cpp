/**
 * @brief reinterpret_cast<PtrType> - use for raw byte conversion (unsafe)
 *
 */
#include "../common.hpp"

#include <array>
#include <cstring>

template <typename T>
T basicUB(double x) {
    T* ptr = reinterpret_cast<T*>(&x);
    T underlying_obj = *ptr; // UB
    return underlying_obj;
}

// https://www.youtube.com/watch?v=L06nbZXD2D0
struct Coord {
    int32_t x;
    int32_t y;
};

constexpr size_t offset{2};

void loveUB(char* blob, const Coord c) {
    reinterpret_cast<Coord*>(blob)[offset].x = c.x; // UB
    reinterpret_cast<Coord*>(blob)[offset].y = c.y; // UB
}

void hateUB(char* blob, const Coord c) {
    std::memcpy(blob + sizeof(Coord) * offset, &c, sizeof(c));
}

int main() {
    // std::cout << basicUB<int32_t>(3.14) << std::endl;

    constexpr size_t byte_sz = 32;
    {
        std::array<char, byte_sz> blob;
        blob.fill(0xF);

        loveUB(blob.data(), Coord{0xA, 0xB});

        for (const auto& b : blob) {
            std::cout << std::hex << static_cast<int32_t>(b) << " ";
        }
        std::cout << std::endl;
        std::cout << std::dec;
    }

    {
        std::array<char, byte_sz> blob;
        blob.fill(0xF);

        // hateUB(blob.data(), Coord{0xC, 0xD});

        for (const auto& b : blob) {
            std::cout << std::hex << static_cast<int32_t>(b) << " ";
        }
        std::cout << std::endl;
        std::cout << std::dec;
    }
}