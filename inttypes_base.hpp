#pragma once

#include <cinttypes>
#include <climits>
#include <string>

template <typename HeadT, typename TailT>
class _uint {
public:
  _uint();
  template <typename other_uint> _uint(other_uint);

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
    return ((static_cast<uint16_t>(_head) << (sizeof(TailT) * CHAR_BIT))
      + static_cast<uint16_t>(_tail));
  }

  operator uint32_t() const {
    return ((static_cast<uint32_t>(_head) << (sizeof(TailT) * CHAR_BIT))
      + static_cast<uint32_t>(_tail));
  }

  operator uint64_t() const {
    return ((static_cast<uint64_t>(_head) << (sizeof(TailT) * CHAR_BIT))
      + static_cast<uint64_t>(_tail));
  }

  const HeadT& _get_head() const {
    return _head;
  }

  const TailT& _get_tail() const {
    return _tail;
  }

protected:
  HeadT _head;
  TailT _tail;
};

namespace std {
template <typename HeadT, typename TailT>
std::string to_string(const _uint<HeadT, TailT>& num) {
  static const _uint<HeadT, TailT> _null(0);
  static const _uint<HeadT, TailT> _ten(10);
  _uint<HeadT, TailT> _num(num);
  std::string res;
  _uint<HeadT, TailT> base(1);
  while (base * _ten <= _num) {
    base *= _ten;
  }
  std::cout << "aba" << std::endl;
  while (base != _null) {
    std::cout << "caba" << std::endl;
    uint8_t div = _num / base;
    base /= _ten;
  }
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
_uint<HeadT, TailT>::_uint(other_uint num)
: _head(num >> (sizeof(TailT) * CHAR_BIT))
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
  // if (_head < num._head) {
  //   return true;
  // } else if (_head == num._head) {
  //   if (_tail < num._tail) {
  //     return true;
  //   }
  // }
  // return false;
  return ((_head < num._head) || (_head == num._head && _tail < num._tail));
}

template <typename HeadT, typename TailT>
const bool _uint<HeadT, TailT>::operator>(const _uint& num) const {
  // if (_head > num._head) {
  //   return true;
  // } else if (_head == num._head) {
  //   if (_tail > num._tail) {
  //     return true;
  //   }
  // }
  // return false;
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
  return !((bool)*this);
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
  ~res._head;
  ~res._tail;
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
  const TailT tail_dif = _tail - num._tail;
  if (tail_dif > _tail) {  // overflow
    --_head;
  }
  _head -= num._head;
  _tail = tail_dif;
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
  uint8_t _num = num;
  _head <<= _num;
  _head ^= HeadT(_tail >> (sizeof(TailT) * CHAR_BIT - _num));
  _tail <<= _num;
  return *this;
}

template <typename HeadT, typename TailT>
template <typename move_uint>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator>>=(move_uint num) {
  uint8_t _num = num;
  _tail >>= _num;
  _tail ^= HeadT(_head << (sizeof(TailT) * CHAR_BIT - _num));
  _head >>= _num;
  return *this;
}
