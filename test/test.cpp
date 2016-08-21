#include <iostream>
#include "../lib/inttypes.hpp"

using Type = pkr::uint56_t;

int main() {
  std::size_t n;
  std::cin >> n;
  for (std::size_t i = 0; i < n; ++i) {
    Type a;
    Type b;
    std::cin >> a >> b;
    std::cout << a + b << ' ';
    std::cout << a - b << ' ';
    std::cout << a * b << ' ';
    std::cout << a / b << std::endl;
  }
  return 0;
}
