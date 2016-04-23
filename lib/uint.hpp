#pragma once

#include <cinttypes>
#include <cstddef>
#include <algorithm>
#include <istream>
#include <ostream>
#include <string>
#include "uint_base.hpp"
#include "utils.hpp"

namespace std {
using pkr::_uint;

template <typename HeadT, typename TailT>
std::string to_string(const _uint<HeadT, TailT>& num, const uint8_t base = 10) {
  const _uint<HeadT, TailT> _base(base);
  _uint<HeadT, TailT> _num(num);
  std::string res;
  while (_num) {
    const _uint<HeadT, TailT> qwe = _num;
    uint8_t digit = _num % _base;
    if ((_num - _uint<HeadT, TailT>(digit)) % _base != _uint<HeadT, TailT>(0)) {
      std::cout << "blyaaa[0]" << std::endl;
    }
    res.push_back('0' + digit);
    _num /= _base;
    if (_num * _base + _uint<HeadT, TailT>(digit) != qwe) {
      std::cout << "blyaaa[1]" << std::endl;
    }
  }
  if (res.empty()) {
    res.push_back('0');
  }
  std::reverse(res.begin(), res.end());
  res.shrink_to_fit();
  return res;
}

template <typename HeadT, typename TailT>
std::istream& operator>>(std::istream& istr, _uint<HeadT, TailT>& num) {
  std::string s;
  istr >> s;
  num = _uint<HeadT, TailT>(s);
  return istr;
}

template <typename HeadT, typename TailT>
std::ostream& operator<<(std::ostream& ostr, const _uint<HeadT, TailT>& num) {
  return (ostr << std::to_string(num));
}

}

namespace pkr {

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

template <typename HeadT, typename TailT, typename other_uint>
const bool operator==(const _uint<HeadT, TailT>& lhs,
  const other_uint& rhs) {
  return (lhs == _uint<HeadT, TailT>(rhs));
}

template <typename HeadT, typename TailT, typename other_uint>
const bool operator!=(const _uint<HeadT, TailT>& lhs,
  const other_uint& rhs) {
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
  return (res <<= static_cast<std::size_t>(rhs));
}

template <typename HeadT, typename TailT, typename mvT>
const _uint<HeadT, TailT> operator>>(const _uint<HeadT, TailT>& lhs,
  const mvT& rhs) {
  _uint<HeadT, TailT> res(lhs);
  return (res >>= static_cast<std::size_t>(rhs));
}

}  // namespace pkr
