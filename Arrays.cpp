#include "common.hpp"

void foo(int*) { PRINT_CALL(); }

template <typename T, size_t sz>
size_t getArrSize(T (&arr)[sz]) {
    return sz;
}

int main() {
    constexpr size_t sz = 42;
    int* arr1 = new int[sz]{};

    int arr2[]{1, 2, 3};

    foo(arr1);
    foo(arr2);

    // std::cout << getArrSize(arr1) << std::endl; // error: no matching
    // function call to ‘getArrSize(int*&)’
    std::cout << getArrSize(arr2) << std::endl;

    delete[] arr1;
}