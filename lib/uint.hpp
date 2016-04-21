#pragma once

#include <cinttypes>
#include <cstddef>
#include <algorithm>
#include <string>
#include "uint_base.hpp"
#include "utils.hpp"

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
const _uint<HeadT, TailT> operator+(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res += rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator-(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res -= rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator*(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res *= rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator/(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res /= rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator%(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res %= rhs);
}

template <typename HeadT, typename TailT>
const bool operator==(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return (lhs.head() == rhs.head() && lhs.tail() == rhs.tail());
}

template <typename HeadT, typename TailT>
const bool operator!=(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return !(lhs == rhs);
}

template <typename HeadT, typename TailT>
const bool operator<(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return ((lhs.head() < rhs.head()) ||
    (lhs.head() == rhs.head() && lhs.tail() < rhs.tail()));
}

template <typename HeadT, typename TailT>
const bool operator>(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return ((lhs.head() > rhs.head()) ||
    (lhs.head() == rhs.head() && lhs.tail() > rhs.tail()));
}

template <typename HeadT, typename TailT>
const bool operator<=(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return !(lhs > rhs);
}

template <typename HeadT, typename TailT>
const bool operator>=(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return !(lhs < rhs);
}

template <typename HeadT, typename TailT>
const bool operator!(const _uint<HeadT, TailT>& lhs) {
  return !(bool(lhs));
}

template <typename HeadT, typename TailT>
const bool operator&&(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return (!!lhs && !!rhs);
}

template <typename HeadT, typename TailT>
const bool operator||(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  return (!!lhs || !!rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator~(const _uint<HeadT, TailT>& lhs) {
  const auto h = ~lhs.head();
  const auto t = ~lhs.tail();
  const _uint<HeadT, TailT> res(h, t);
  return res;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator&(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res &= rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator|(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res |= rhs);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> operator^(const _uint<HeadT, TailT>& lhs,
  const _uint<HeadT, TailT>& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res ^= rhs);
}

template <typename HeadT, typename TailT, typename mvT>
const _uint<HeadT, TailT> operator<<(const _uint<HeadT, TailT>& lhs,
  const mvT& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res <<= rhs);
}

template <typename HeadT, typename TailT, typename mvT>
const _uint<HeadT, TailT> operator>>(const _uint<HeadT, TailT>& lhs,
  const mvT& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res >>= rhs);
}
