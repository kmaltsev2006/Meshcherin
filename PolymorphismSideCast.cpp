#include "common.hpp"

struct Mom {virtual ~Mom() = default;};
struct Dad {virtual ~Dad() = default;};
struct Son : Mom, Dad {};

int main() {
    try {
        // Mom(Son) -> Dad
        Son s;
        dynamic_cast<Dad&>(static_cast<Mom&>(s));
        std::cout << "Success" << std::endl;
    } catch (const std::bad_cast&) {
        std::cout << "Fail" << std::endl;
    }
    
    try {
        // Mom -> Dad
        Mom m;
        dynamic_cast<Dad&>(m);
        std::cout << "Success" << std::endl;
    } catch (const std::bad_cast&) {
        std::cout << "Fail" << std::endl;
    }
}