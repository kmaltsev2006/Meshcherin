#include <iostream>

int sum(int a, int b) { return a + b; }

int main() {
    const int a{10};
    const int b{10};

    printf("%p %p %p\n", sum, *sum, &sum);

    {
        int (*foo)(int, int) = sum;
        auto x = foo(a, b);
        std::cout << x << std::endl;
        printf("%p %p %p\n", foo, *foo, &foo);
    }

    {
        int (*foo)(int, int) = &sum;
        auto x = (*foo)(a, b);
        std::cout << x << std::endl;
        printf("%p %p %p\n", foo, *foo, &foo);
    }

    {
        int (*foo)(int, int) = &sum;
        auto x = foo(a, b);
        std::cout << x << std::endl;
        printf("%p %p %p\n", foo, *foo, &foo);
    }
}