#include <iostream>
#include "../lib/inttypes.hpp"

int main(int argc, char const *argv[]) {
  const uint8_t k = 10;
  std::size_t n;
  std::cin >> n;
  for (std::size_t i = 0; i < n; ++i) {
    std::string u, v;
    std::cin >> u >> v;
    const pkr::uint80_t a{u};
    const pkr::uint80_t b{v};
    std::cout << std::to_string(a + b, k) << " "
              << std::to_string(a - b, k) << " "
              << std::to_string(a * b, k) << " "
              << std::to_string(a / b, k) << std::endl;
  }
  return 0;
}
