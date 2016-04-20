#include <cstdlib>
#include <ctime>
#include <iostream>
#include "inttypes.hpp"

size_t errors = 0;

void check(const uint32_t u, const uint32_t v) {
  const uint96_t a(u);
  const uint96_t b(v);
  // std::cout << u << " == " << std::to_string(a) << std::endl;
  if (uint32_t(u + v) != uint32_t(a + b)) {
    // std::cout << uint64_t(u + v) << " != " << uint64_t(a + b) << std::endl;
    ++errors;
  }
  // if (uint32_t(u - v) != uint32_t(a - b)) {
  //   ++errors;
  // }
  if (uint32_t(u * v) != uint32_t(a * b)) {
    ++errors;
  }
  // if (uint32_t(u / v) != uint32_t(a / b)) {
  //   ++errors;
  // }
}

inline uint32_t f(uint32_t n) {
  return 103 * n * n * n + 51 * n * n + 25 * n + 12;
}

int main() {
  size_t s = f(time(nullptr));
  for (size_t i = 0; i < 1e3; ++i) {
    uint32_t u = f(s++);
    uint32_t v = f(s++);
    check(u, v);
  }
  std::cout << errors << std::endl;
  return 0;
}
