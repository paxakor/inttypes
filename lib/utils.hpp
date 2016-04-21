#pragma once

#include <climits>
#include <cstddef>

template <typename Type>
inline std::size_t bits_size_of() {
  return sizeof(Type) * CHAR_BIT;
}

template <typename Type>
inline std::size_t bits_size_of(const Type& num) {
  return bits_size_of<Type>();
}

template <typename Type>
std::size_t bits_len(const Type& num) {
  std::size_t len = 0;
  auto tmp(num);
  while (tmp != Type(0)) {
    ++len;
    tmp >>= 1;
  }
  return len;
}
