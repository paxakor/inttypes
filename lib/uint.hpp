#pragma once

#include <cstddef>
#include <algorithm>
#include <istream>
#include <ostream>
#include <string>
#include <type_traits>
#include "uint_base.hpp"
#include "util.hpp"


namespace std {

template <typename HeadT, typename TailT>
std::string to_string(pkr::Uint<HeadT, TailT> num, const uint8_t base = 10) {
  std::string res;
  while (num) {
    const uint8_t digit{num % base};
    res.push_back('0' + digit);
    num /= base;
  }
  if (res.empty()) {
    res.push_back('0');
  }
  std::reverse(res.begin(), res.end());
  return res;
}

}

template <typename HeadT, typename TailT>
std::istream& operator>>(std::istream& istr, pkr::Uint<HeadT, TailT>& num) {
  std::string s;
  istr >> s;
  num = pkr::Uint<HeadT, TailT>(s);
  return istr;
}

template <typename HeadT, typename TailT>
std::ostream& operator<<(std::ostream& ostr,
                         const pkr::Uint<HeadT, TailT>& num) {
  return ostr << std::to_string(num);
}


namespace pkr {

template <typename A, typename B>
using UintCommon = std::conditional_t<(sizeof(A) >= sizeof(B)), A, B>;

#define OPERATOR_FOR_OTHER(op)                                                 \
template <typename HeadT, typename TailT, typename OtherUint>                  \
inline constexpr auto operator op(const Uint<HeadT, TailT>& lhs,               \
                                  const OtherUint& rhs) noexcept {             \
  return static_cast<UintCommon<Uint<HeadT, TailT>, OtherUint>>(lhs)           \
      op static_cast<UintCommon<Uint<HeadT, TailT>, OtherUint>>(rhs);          \
}

#define BOOL_OPERATOR(op)                                                      \
template <typename HeadT, typename TailT>                                      \
inline constexpr bool operator op(const Uint<HeadT, TailT>& lhs,               \
                                  const Uint<HeadT, TailT>& rhs) noexcept

#define OPERATOR_FOR_SAME(op)                                                  \
template <typename HeadT, typename TailT> constexpr                            \
Uint<HeadT, TailT> operator op(const Uint<HeadT, TailT>& lhs,                  \
                               const Uint<HeadT, TailT>& rhs) noexcept {       \
  Uint<HeadT, TailT> res(lhs);                                                 \
  return res op##= rhs;                                                        \
}

#define OPERATORS(op) \
OPERATOR_FOR_SAME(op) \
OPERATOR_FOR_OTHER(op)


BOOL_OPERATOR(==) {
  return lhs.head() == rhs.head() && lhs.tail() == rhs.tail();
}

BOOL_OPERATOR(!=) {
  return !(lhs == rhs);
}

BOOL_OPERATOR(<) {
  return lhs.head() < rhs.head() ||
    (lhs.head() == rhs.head() && lhs.tail() < rhs.tail());
}

BOOL_OPERATOR(>) {
  return lhs.head() > rhs.head() ||
    (lhs.head() == rhs.head() && lhs.tail() > rhs.tail());
}

BOOL_OPERATOR(<=) {
  return !(lhs > rhs);
}

BOOL_OPERATOR(>=) {
  return !(lhs < rhs);
}

OPERATOR_FOR_OTHER(<)
OPERATOR_FOR_OTHER(>)
OPERATOR_FOR_OTHER(<=)
OPERATOR_FOR_OTHER(>=)
OPERATOR_FOR_OTHER(==)
OPERATOR_FOR_OTHER(!=)

OPERATORS(+)
OPERATORS(-)
OPERATORS(*)
OPERATORS(/)
OPERATORS(%)
OPERATORS(&)
OPERATORS(^)
OPERATORS(|)
// OPERATORS(<<)
// OPERATORS(>>)

#undef BOOL_OPERATOR
#undef OPERATOR_FOR_OTHER
#undef OPERATOR_FOR_SAME
#undef OPERATORS


template <typename HeadT, typename TailT>
inline constexpr auto operator~(const Uint<HeadT, TailT>& lhs) {
  return Uint<HeadT, TailT>{~(lhs.head()), ~(lhs.tail())};
}

template <typename HeadT, typename TailT>
inline constexpr bool operator!(const Uint<HeadT, TailT>& lhs) {
  return !static_cast<bool>(lhs);
}

template <typename HeadT, typename TailT> constexpr
inline auto operator<<(Uint<HeadT, TailT> lhs, uint32_t rhs) noexcept {
  return lhs <<= rhs;
}

template <typename HeadT, typename TailT> constexpr
inline auto operator>>(Uint<HeadT, TailT> lhs, uint32_t rhs) noexcept {
  return lhs >>= rhs;
}

template <typename HeadT, typename TailT, typename OtherUint> constexpr
inline auto operator<<(Uint<HeadT, TailT> lhs, const OtherUint& rhs) noexcept {
  return lhs << static_cast<uint32_t>(rhs);
}

template <typename HeadT, typename TailT, typename OtherUint> constexpr
inline auto operator>>(Uint<HeadT, TailT> lhs, const OtherUint& rhs) noexcept {
  return lhs >> static_cast<uint32_t>(rhs);
}

}  // namespace pkr
