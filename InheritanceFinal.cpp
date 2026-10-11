#include "common.hpp"

struct FirstBase {};
struct LastBase final /*prohibs inheritance from LastBase*/ : FirstBase {};

// error: cannot derive from ‘final’ base ‘LastBase’ in derived type ‘MaybeOneMoreBase’
struct MaybeOneMoreBase : LastBase {};

int main() {}