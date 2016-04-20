#include <cstdlib>
#include <ctime>
#include <iostream>
#include "inttypes.hpp"

size_t errors = 0;

void check(uint32_t u, uint32_t v) {
  uint56_t a(u);
  uint56_t b(v);
  // std::cout << u << " == " << std::to_string(a) << std::endl;
  if (std::to_string(u + v) != std::to_string(a + b)) {
    ++errors;
  }
  if (std::to_string(u - v) != std::to_string(a - b)) {
    ++errors;
  }
  // if (std::to_string(u * v) != std::to_string(a * b)) {
  //   ++errors;
  // }
  // if (std::to_string(u / v) != std::to_string(a / b)) {
  //   ++errors;
    // std::cout << (a / b).to_string() << std::endl;
  // }
}

int main() {
  size_t s = time(nullptr);
  for (size_t i = 0; i < 1e4; ++i) {
    srand(s++);
    uint32_t u = rand();
    uint32_t v = rand();
    check(u, v);
  }
  std::cout << errors << std::endl;
  return 0;
}
