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
using pkr::Uint;

template <typename HeadT, typename TailT>
std::string to_string(const Uint<HeadT, TailT>& num, const uint8_t base = 10) {
  const Uint<HeadT, TailT> _base(base);
  Uint<HeadT, TailT> _num(num);
  std::string res;
  while (_num) {
    const Uint<HeadT, TailT> qwe = _num;
    uint8_t digit = _num % _base;
    if ((_num - Uint<HeadT, TailT>(digit)) % _base != Uint<HeadT, TailT>(0)) {
      std::cout << "blyaaa[0]" << std::endl;
    }
    res.push_back('0' + digit);
    _num /= _base;
    if (_num * _base + Uint<HeadT, TailT>(digit) != qwe) {
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
std::istream& operator>>(std::istream& istr, Uint<HeadT, TailT>& num) {
  std::string s;
  istr >> s;
  num = Uint<HeadT, TailT>(s);
  return istr;
}

template <typename HeadT, typename TailT>
std::ostream& operator<<(std::ostream& ostr, const Uint<HeadT, TailT>& num) {
  return (ostr << std::to_string(num));
}

}

namespace pkr {

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator+(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res += rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator-(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res -= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator*(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res *= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator/(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res /= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator%(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res %= rhs);
}

template <typename HeadT, typename TailT>
const bool operator==(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  return (lhs.head() == rhs.head() && lhs.tail() == rhs.tail());
}

template <typename HeadT, typename TailT, typename otherUint>
const bool operator==(const Uint<HeadT, TailT>& lhs,
  const otherUint& rhs) {
  return (lhs == Uint<HeadT, TailT>(rhs));
}

template <typename HeadT, typename TailT, typename otherUint>
const bool operator!=(const Uint<HeadT, TailT>& lhs,
  const otherUint& rhs) {
  return !(lhs == rhs);
}

template <typename HeadT, typename TailT>
const bool operator<(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  return ((lhs.head() < rhs.head()) ||
    (lhs.head() == rhs.head() && lhs.tail() < rhs.tail()));
}

template <typename HeadT, typename TailT>
const bool operator>(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  return ((lhs.head() > rhs.head()) ||
    (lhs.head() == rhs.head() && lhs.tail() > rhs.tail()));
}

template <typename HeadT, typename TailT>
const bool operator<=(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  return !(lhs > rhs);
}

template <typename HeadT, typename TailT>
const bool operator>=(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  return !(lhs < rhs);
}

template <typename HeadT, typename TailT>
const bool operator!(const Uint<HeadT, TailT>& lhs) {
  return !(bool(lhs));
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator&(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res &= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator|(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res |= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator^(const Uint<HeadT, TailT>& lhs,
  const Uint<HeadT, TailT>& rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res ^= rhs);
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator<<(const Uint<HeadT, TailT>& lhs,
  size_t rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res <<= static_cast<std::size_t>(rhs));
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> operator>>(const Uint<HeadT, TailT>& lhs,
  size_t rhs) {
  Uint<HeadT, TailT> res(lhs);
  return (res >>= static_cast<std::size_t>(rhs));
}

}  // namespace pkr
