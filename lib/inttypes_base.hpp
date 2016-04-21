#pragma once

#include <cinttypes>
#include <cstddef>
#include <algorithm>
#include <string>
#include "utils.hpp"

template <typename HeadT, typename TailT>
class _uint {
public:
  _uint();
  template <typename other_uint> _uint(const other_uint&);

  const _uint& operator=(const _uint&);
  const _uint operator+(const _uint&) const;
  const _uint operator-(const _uint&) const;
  const _uint operator*(const _uint&) const;
  const _uint operator/(const _uint&) const;
  const _uint operator%(const _uint&) const;
  const _uint& operator++();
  const _uint operator++(int);
  const _uint& operator--();
  const _uint operator--(int);
  const bool operator==(const _uint&) const;
  const bool operator!=(const _uint&) const;
  const bool operator<(const _uint&) const;
  const bool operator>(const _uint&) const;
  const bool operator<=(const _uint&) const;
  const bool operator>=(const _uint&) const;
  const bool operator!() const;
  const bool operator&&(const _uint&) const;
  const bool operator||(const _uint&) const;
  const _uint operator~() const;
  const _uint operator&(const _uint&) const;
  const _uint operator|(const _uint&) const;
  const _uint operator^(const _uint&) const;
  const _uint& operator+=(const _uint&);
  const _uint& operator-=(const _uint&);
  const _uint& operator*=(const _uint&);
  const _uint& operator/=(const _uint&);
  const _uint& operator%=(const _uint&);
  const _uint& operator&=(const _uint&);
  const _uint& operator|=(const _uint&);
  const _uint& operator^=(const _uint&);

  template <typename move_uint> const _uint operator<<(move_uint) const;
  template <typename move_uint> const _uint operator>>(move_uint) const;
  template <typename move_uint> const _uint& operator<<=(move_uint);
  template <typename move_uint> const _uint& operator>>=(move_uint);

  operator bool() const {
    return (_head || _tail);
  }

  operator uint8_t() const {
    return static_cast<uint8_t>(_tail);
  }

  operator uint16_t() const {
    return ((static_cast<uint16_t>(_head) << bits_size_of<TailT>())
      + static_cast<uint16_t>(_tail));
  }

  operator uint32_t() const {
    return ((static_cast<uint32_t>(_head) << bits_size_of<TailT>())
      + static_cast<uint32_t>(_tail));
  }

  operator uint64_t() const {
    return ((static_cast<uint64_t>(_head) << bits_size_of<TailT>())
      + static_cast<uint64_t>(_tail));
  }

private:
  HeadT _head;
  TailT _tail;
};

namespace std {

template <typename HeadT, typename TailT>
std::string to_string(const _uint<HeadT, TailT>& num, const uint8_t base = 10) {
  static const _uint<HeadT, TailT> _null(0);
  static const _uint<HeadT, TailT> _one(1);
  // static const _uint<HeadT, TailT> _ten(10);
  std::string res;
  _uint<HeadT, TailT> _num(num);
  // _uint<HeadT, TailT> base(1);
  // while (base * _ten <= _num) {
  //   base *= _ten;
  // }
  // while (base != _null) {
  //   uint8_t div = _num / base;
  //   _num %= base;
  //   base /= _ten;
  //   res.push_back('0' + div);
  // }
  while(_num != _null) {
    if (_num & _one)
      res.push_back('1');
    else
      res.push_back('0');
    _num >>= 1;
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
_uint<HeadT, TailT>::_uint()
: _head(0)
, _tail(0) {}

#pragma GCC diagnostic ignored "-Wshift-count-overflow"
template <typename HeadT, typename TailT>
template <typename other_uint>
_uint<HeadT, TailT>::_uint(const other_uint& num)
: _head(bits_size_of<TailT>() < bits_size_of<other_uint>() ?
    num >> bits_size_of<TailT>() : 0)
, _tail(num) {}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator=(const _uint& num) {
  _head = num._head;
  _tail = num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator+(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res += num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator-(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res -= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator*(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res *= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator/(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res /= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator%(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res %= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator++() {
  if (_tail + 1 < _tail) {
    ++_head;
  }
  ++_tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator++(int) {
  const _uint<HeadT, TailT> res(*this);
  ++(*this);
  return res;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator--() {
  if (_tail - 1 > _tail) {
    --_head;
  }
  --_tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator--(int) {
  const _uint<HeadT, TailT> res(*this);
  --(*this);
  return res;
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator==(const _uint& num) const {
  return (_head == num._head && _tail == num._tail);
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator!=(const _uint& num) const {
  return !(*this == num);
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator<(const _uint& num) const {
  return ((_head < num._head) || (_head == num._head && _tail < num._tail));
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator>(const _uint& num) const {
  return ((_head > num._head) || (_head == num._head && _tail > num._tail));
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator<=(const _uint& num) const {
  return !(*this > num);
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator>=(const _uint& num) const {
  return !(*this < num);
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator!() const {
  return !(bool(*this));
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator&&(const _uint& num) const {
  return (!!(*this) && !!(num));
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator||(const _uint& num) const {
  return (!!(*this) || !!(num));
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator~() const {
  _uint<HeadT, TailT> res(*this);
  res._head = ~res._head;
  res._tail = ~res._tail;
  return res;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator&(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res &= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator|(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res |= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator^(const _uint& num) const {
  _uint<HeadT, TailT> res(*this);
  return (res ^= num);
}

template <typename HeadT, typename TailT>
template <typename move_uint>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator<<(move_uint num) const {
  _uint<HeadT, TailT> res(*this);
  return (res <<= num);
}

template <typename HeadT, typename TailT>
template <typename move_uint>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator>>(move_uint num) const {
  _uint<HeadT, TailT> res(*this);
  return (res >>= num);
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator+=(const _uint& num) {
  const TailT tail_sum = _tail + num._tail;
  if (tail_sum < _tail) {  // overflow
    ++_head;
  }
  _head += num._head;
  _tail = tail_sum;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator-=(const _uint& num) {
  if (*this >= num) {
    const TailT tail_dif = _tail - num._tail;
    if (tail_dif > _tail) {  // overflow
      --_head;
    }
    _head -= num._head;
    _tail = tail_dif;
  } else {
    *this = ~(num - *this);
    ++(*this);
  }
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator*=(const _uint& num) {
  static const _uint<HeadT, TailT> _null(0);
  static const _uint<HeadT, TailT> _one(1);
  _uint<HeadT, TailT> mul(num < *this ? num : *this);
  _uint<HeadT, TailT> val(num > *this ? num : *this);
  // _uint<HeadT, TailT> mul(num);
  // _uint<HeadT, TailT> val(*this);
  _uint<HeadT, TailT> res(_null);
  while (mul != _null) {
    if (!!(mul & _one)) {
      res += val;
    }
    mul >>= 1;
    val <<= 1;
  }
  *this = res;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator/=(const _uint& num) {
  static const _uint<HeadT, TailT> _one(1);
  _uint<HeadT, TailT> digit_bit(_one);
  _uint<HeadT, TailT> tmp(*this);
  _uint<HeadT, TailT> res(0);
  _uint<HeadT, TailT> base(digit_bit * num);
  while (base <= tmp) {
    digit_bit <<= 1;
    base <<= 1;
  }
  while (digit_bit != _one) {
    digit_bit >>= 1;
    base >>= 1;
    if (base <= tmp) {
      tmp -= base;
      res += digit_bit;
    }
  }
  *this = res;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator%=(const _uint& num) {
  *this -= ((*this / num) * num);
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator&=(const _uint& num) {
  _head &= num._head;
  _tail &= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator|=(const _uint& num) {
  _head |= num._head;
  _tail |= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator^=(const _uint& num) {
  _head ^= num._head;
  _tail ^= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
template <typename move_uint>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator<<=(move_uint num) {
  std::size_t _num = num;
  _head <<= _num;
  _head ^= HeadT(_tail >> (bits_size_of<TailT>() - _num));
  _tail <<= _num;
  return *this;
}

template <typename HeadT, typename TailT>
template <typename move_uint>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator>>=(move_uint num) {
  std::size_t _num = num;
  _tail >>= _num;
  _tail ^= TailT(_head) << (bits_size_of<TailT>() - _num);
  _head >>= _num;
  return *this;
}
