#pragma once

#include <cxxabi.h>
#include <print>
#include <iostream>
#include <iomanip>
#include <cstdint>

#define PRINT_CALL() (std::cout << __PRETTY_FUNCTION__ << std::endl)

template <typename T>
void printTypeCE() = delete;

template <typename T>
void printTypeNoCE(T) {
    char* demangled =
        abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    std::cout << demangled << std::endl;
    std::free(demangled);
}

template<typename T>
void printBytes(const T& t, const size_t sz=sizeof(T)) {
    std::cout << "Address: " << &t << std::endl;
    auto raw_bytes = std::bit_cast<const unsigned char*>(&t);
    std::cout << std::hex;
    for (size_t i = 0; i < sz + 1; ++i) {
        if (i % sizeof(void*) == 0) {
            std::cout << "|";
        } else if constexpr (sizeof(void*) > 0) {
            if (i % (sizeof(void*)/2) == 0)
                std::cout << ".";
        }
        
        if (i != sz)
        std::cout << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<uint32_t>(raw_bytes[i]);
    }
    std::cout << std::dec;
    std::cout << std::endl;
}

template<typename T>
void printInfo() {
    T t;
    std::cout << "Size: " << sizeof(t) << std::endl;
    printBytes(t);
    std::cout << std::endl;
}
