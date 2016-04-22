#include <iostream>
#include "../lib/inttypes.hpp"

int main(int argc, char const *argv[]) {
  std::string u, v;
  if (argc < 3) {
    return 1;
  }
  const pkr::uint80_t a{std::string(argv[1])};
  const pkr::uint80_t b{std::string(argv[2])};
  const uint8_t k = 10;
  std::cout << std::to_string(a + b, k) << std::endl
            << std::to_string(a - b, k) << std::endl
            << std::to_string(a * b, k) << std::endl
            << std::to_string(a / b, k) << std::endl;
  return 0;
}
