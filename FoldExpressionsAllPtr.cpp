/**
 * 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
 * 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
 */
#include "common.hpp"

#include <type_traits>

// op: &&
// E: std::id_pointer_v<Ts>
template<typename... Ts>
struct AllPointers {
  static constexpr bool value = (std::is_pointer_v<Ts> && ...);
};

template<typename... Ts>
constexpr bool AllPointers_v = AllPointers<Ts...>::value;

int main() {
  std::print("{}\n", AllPointers_v<int*, bool*, char*>);
  std::print("{}\n", AllPointers_v<int*, bool*, char>);
}