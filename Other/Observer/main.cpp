#include "LookAtMe.hpp"
#include "Observer.hpp"

void ex4() {
    LookAtMe look_at_me;

    auto o1 = Observer::create(look_at_me);
    auto o2 = Observer::create(look_at_me);

    {
        auto o3 = Observer::create(look_at_me);
        look_at_me.changeSelf();
    }

    look_at_me.changeSelf();
}

int main() { ex4(); }