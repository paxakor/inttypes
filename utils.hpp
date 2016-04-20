#pragma once

#include <climits>
#include <cstddef>

template <typename Type>
inline std::size_t bits_size_of() {
  return sizeof(Type) * CHAR_BIT;
}

template <typename Type>
inline std::size_t bits_size_of(const Type& var) {
  return bits_size_of<Type>();
}
