#include <cstdint>
#include <iostream>

int main() {
    static const auto foo = []<typename T>(T obj) {
        std::cout << typeid(obj).name() << " " << obj << std::endl;
    };

    foo(int{});

    foo.operator()<int>(int{});
    foo.operator()<double>(double{});

    foo.operator()<uint64_t>(int{-1}); // CE with -Werror -Wsign-conversion
}