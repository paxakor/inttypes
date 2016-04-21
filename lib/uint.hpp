#pragma once

#include <cinttypes>
#include <cstddef>
#include <algorithm>
#include <string>
#include "uint_base.hpp"
#include "utils.hpp"

// template <typename HeadT, typename TailT>
// operator bool(const _uint<HeadT, TailT>& num) {
//   return (num.head() || num.tail());
// }

// template <typename HeadT, typename TailT>
// operator uint8_t(const _uint<HeadT, TailT>& num) {
//   return static_cast<uint8_t>(num.tail());
// }

// template <typename HeadT, typename TailT>
// operator uint16_t(const _uint<HeadT, TailT>& num) {
//   return ((static_cast<uint16_t>(num.head()) << bits_size_of<TailT>())
//     + static_cast<uint16_t>(num.tail()));
// }

// template <typename HeadT, typename TailT>
// operator uint32_t(const _uint<HeadT, TailT>& num) {
//   return ((static_cast<uint32_t>(num.head()) << bits_size_of<TailT>())
//     + static_cast<uint32_t>(num.tail()));
// }

// template <typename HeadT, typename TailT>
// operator uint64_t(const _uint<HeadT, TailT>& num) {
//   return ((static_cast<uint64_t>(num.head()) << bits_size_of<TailT>())
//     + static_cast<uint64_t>(num.tail()));
// }

namespace std {
template <typename HeadT, typename TailT>
std::string to_string(const _uint<HeadT, TailT>& num, const uint8_t base = 10) {
  static const _uint<HeadT, TailT> _null(0);
  static const _uint<HeadT, TailT> _one(1);
  const _uint<HeadT, TailT> _base(base);
  _uint<HeadT, TailT> _num(num);
  std::string res;
  while (_num != _null) {
    uint8_t digit = _num % _base;
    res.push_back('0' + digit);
    _num /= base;
  }
  if (res.empty()) {
    res.push_back('0');
  }
  std::reverse(res.begin(), res.end());
  res.shrink_to_fit();
  return res;
}
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator+(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res += second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator-(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res -= second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator*(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res *= second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator/(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res /= second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator%(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res %= second);
}

template <typename HeadT, typename TailT>
const bool operator==(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return (first.head() == second.head() && first.tail() == second.tail());
}

template <typename HeadT, typename TailT>
const bool operator!=(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return !(first == second);
}

template <typename HeadT, typename TailT>
const bool operator<(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return ((first.head() < second.head()) || (first.head() == second.head() && first.tail() < second.tail()));
}

template <typename HeadT, typename TailT>
const bool operator>(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return ((first.head() > second.head()) || (first.head() == second.head() && first.tail() > second.tail()));
}

template <typename HeadT, typename TailT>
const bool operator<=(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return !(first > second);
}

template <typename HeadT, typename TailT>
const bool operator>=(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return !(first < second);
}

template <typename HeadT, typename TailT>
const bool operator!(const _uint<HeadT, TailT>& first) {
  return !(bool(first));
}

template <typename HeadT, typename TailT>
const bool operator&&(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return (!!first && !!second);
}

template <typename HeadT, typename TailT>
const bool operator||(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  return (!!first || !!second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator~(const _uint<HeadT, TailT>& first) {
  const auto h = ~first.head();
  const auto t = ~first.tail();
  const _uint<HeadT, TailT> res(h, t);
  return res;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator&(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res &= second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator|(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res |= second);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator^(const _uint<HeadT, TailT>& first, const _uint<HeadT, TailT>& second) {
  _uint<HeadT, TailT> res(first);
  return (res ^= second);
}

template <typename HeadT, typename TailT, typename move_uint>
const _uint<HeadT, TailT> operator<<(const _uint<HeadT, TailT>& first, const move_uint& second) {
  _uint<HeadT, TailT> res(first);
  return (res <<= second);
}

template <typename HeadT, typename TailT, typename move_uint>
const _uint<HeadT, TailT> operator>>(const _uint<HeadT, TailT>& first, const move_uint& second) {
  _uint<HeadT, TailT> res(first);
  return (res >>= second);
}
