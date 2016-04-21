#include <iostream>
#include "../lib/inttypes.hpp"

int main(int argc, char const *argv[]) {
  uint64_t u, v;
  if (argc > 2) {
    u = std::stoull(argv[1]);
    v = std::stoull(argv[2]);
  } else {
    std::cin >> u >> v;
  }
  const uint24_t a(u);
  const uint24_t b(v);
  std::cout << std::to_string(a + b, 2) << std::endl
            << std::to_string(a - b, 2) << std::endl
            << std::to_string(a * b, 2) << std::endl
            << std::to_string(a / b, 2) << std::endl;
  return 0;
}
