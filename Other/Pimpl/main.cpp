#include "API.hpp"

API getApi() { return API{}; }

int main() {
    API api1;
    api1 = api1;
    API api2{api1};
    API api3 = api2;
    API api4{getApi()};

    api1.foo();
    api2.foo();
    api3.foo();
    api4.foo();
}