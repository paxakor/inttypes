#pragma once
#pragma GCC diagnostic ignored "-Wshift-count-overflow"

#include <cinttypes>
#include <cstddef>
#include <stdexcept>
#include <string>
#include "uint.hpp"
#include "utils.hpp"

namespace pkr {

template <typename HeadT, typename TailT>
class Uint {
public:
  Uint();
  Uint(const HeadT&, const TailT&);
  template <typename otherUint> Uint(const otherUint&);
  Uint(const std::string&, const uint8_t = 10);

  const Uint operator~() const;
  const Uint operator++(int);
  const Uint operator--(int);
  const Uint& operator++();
  const Uint& operator--();
  const Uint& operator=(const Uint&);
  const Uint& operator+=(const Uint&);
  const Uint& operator-=(const Uint&);
  const Uint& operator*=(const Uint&);
  const Uint& operator/=(const Uint&);
  const Uint& operator%=(const Uint&);
  const Uint& operator&=(const Uint&);
  const Uint& operator^=(const Uint&);
  const Uint& operator|=(const Uint&);
  const Uint& operator<<=(ssize_t);
  const Uint& operator>>=(ssize_t);

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

  const HeadT& head() const {
    return _head;
  }

  const TailT& tail() const {
    return _tail;
  }

private:
  HeadT _head;
  TailT _tail;
};

template <typename HeadT, typename TailT>
Uint<HeadT, TailT>::Uint()
  : _head(0)
  , _tail(0) {}

template <typename HeadT, typename TailT>
Uint<HeadT, TailT>::Uint(const HeadT& h, const TailT& t)
  : _head(h)
  , _tail(t) {}

template <typename HeadT, typename TailT>
template <typename otherUint>
Uint<HeadT, TailT>::Uint(const otherUint& num)
  : _head(bits_size_of<TailT>() < bits_size_of<otherUint>() ?
      num >> bits_size_of<TailT>() : 0)
  , _tail(num) {}

template <typename HeadT, typename TailT>
Uint<HeadT, TailT>::Uint(const std::string& str, const uint8_t base)
  : _head(0)
  , _tail(0) {
  Uint<HeadT, TailT> digit(1);
  for (auto iter = str.rbegin(); iter != str.rend(); ++iter) {
    *this += (digit * Uint<HeadT, TailT>(*iter - '0'));
    digit *= base;
  }
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator=(const Uint& num) {
  _head = num._head;
  _tail = num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator++() {
  const auto tmp = _tail;
  ++_tail;
  if (_tail < tmp) {
    ++_head;
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> Uint<HeadT, TailT>::operator++(int) {
  const Uint<HeadT, TailT> res(*this);
  ++(*this);
  return res;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator--() {
  const auto tmp = _tail;
  --_tail;
  if (_tail > tmp) {
    --_head;
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> Uint<HeadT, TailT>::operator--(int) {
  const Uint<HeadT, TailT> res(*this);
  --(*this);
  return res;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator+=(const Uint& num) {
  const TailT tail_sum = _tail + num._tail;
  if (tail_sum < _tail) {
    ++_head;
  }
  _head += num._head;
  _tail = tail_sum;
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator-=(const Uint& num) {
  if (*this >= num) {
    if (_tail < num._tail) {
      --_head;
    }
    _head -= num._head;
    _tail -= num._tail;
  } else {
    *this = ~(num - *this);
    ++(*this);
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator*=(const Uint& num) {
  Uint<HeadT, TailT> base(num);
  Uint<HeadT, TailT> tmp(*this);
  *this = 0;
  while (tmp) {
    if (static_cast<uint8_t>(tmp) & 1) {
      *this += base;
    }
    tmp >>= 1;
    base <<= 1;
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator/=(const Uint& num) {
  if (num == 0) {
    throw std::runtime_error::runtime_error("division by zero");
  }
  Uint<HeadT, TailT> base(num);
  Uint<HeadT, TailT> digit_bit(1);
  Uint<HeadT, TailT> tmp(base);
  tmp <<= 1;
  while (tmp > base) {
    digit_bit <<= 1;
    base <<= 1;
    tmp <<= 1;
  }
  tmp = *this;
  *this = 0;
  while (num <= tmp) {
    if (base <= tmp) {
      tmp -= base;
      *this += digit_bit;
    }
    digit_bit >>= 1;
    base >>= 1;
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator%=(const Uint& num) {
  return (*this -= ((*this / num) * num));
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator&=(const Uint& num) {
  _head &= num._head;
  _tail &= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator|=(const Uint& num) {
  _head |= num._head;
  _tail |= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator^=(const Uint& num) {
  _head ^= num._head;
  _tail ^= num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT> Uint<HeadT, TailT>::operator~() const {
  Uint<HeadT, TailT> res(*this);
  res._head = ~(res._head);
  res._tail = ~(res._tail);
  return res;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator<<=(ssize_t num) {
  if (num <= 8) {
    _head <<= num;
    _head ^= HeadT(_tail >> (bits_size_of<TailT>() - num));
    _tail <<= num;
  } else {
    *this <<= 8;
    *this <<= (num - 8);
  }
  return *this;
}

template <typename HeadT, typename TailT>
const Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator>>=(ssize_t num) {
  if (num <= 8) {
    _tail >>= num;
    _tail ^= (TailT(_head) << (bits_size_of<TailT>() - num));
    _head >>= num;
  } else {
    *this >>= 8;
    *this >>= (num - 8);
  }
  return *this;
}

}  // namespace pkr
