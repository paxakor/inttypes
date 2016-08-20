#pragma once

#include <climits>
#include <cstddef>

template <typename Type>
constexpr ssize_t bits_size_of() {
  return sizeof(Type) * CHAR_BIT;
}

template <typename Type>
constexpr ssize_t bits_size_of(const Type& num) {
  return bits_size_of<Type>();
}

template <typename Type>
ssize_t bits_len(const Type& num) {
  ssize_t len = 0;
  auto tmp = num;
  while (tmp) {
    ++len;
    tmp >>= 1;
  }
  return len;
}
