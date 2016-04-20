#include <iostream>
#include "../lib/inttypes.hpp"

int main() {
  uint32_t u, v;
  std::cin >> u >> v;
  const uint24_t a(u);
  const uint24_t b(v);
  std::cout << std::to_string(a + b, 2) << std::endl
            << std::to_string(a - b, 2) << std::endl
            << std::to_string(a * b, 2) << std::endl
            << std::to_string(a / b, 2) << std::endl;
  return 0;
}
