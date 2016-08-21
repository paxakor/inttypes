#pragma once

#include <climits>
#include <cstddef>
#include <type_traits>
#include "uint_base.hpp"

namespace pkr {

template <typename HeadT, typename TailT> class Uint;

namespace util {

template <typename Type>
constexpr auto UintSize = sizeof(Type) * CHAR_BIT;

template <typename HeadT, typename TailT>
constexpr auto UintSize<Uint<HeadT, TailT>> = UintSize<HeadT> + UintSize<TailT>;

template <typename Type>
inline constexpr auto bits_size_of() noexcept {
  return UintSize<Type>;
}

template <typename Type>
inline constexpr auto bits_size_of(Type&&) noexcept {
  return bits_size_of<std::decay_t<Type>>();
}

template <typename Type>
constexpr auto bits_len(Type num) {
  size_t len = 0;
  while (num) {
    ++len;
    num >>= 1;
  }
  return len;
}

} // namespace util
} // namespace pkr
