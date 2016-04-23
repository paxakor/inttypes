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
class _uint {
public:
  _uint();
  _uint(const HeadT&, const TailT&);
  template <typename other_uint> _uint(const other_uint&);
  _uint(const std::string&, const uint8_t = 10);

  const _uint operator++(int);
  const _uint operator--(int);
  const _uint& operator++();
  const _uint& operator--();
  const _uint& operator=(const _uint&);
  const _uint& operator+=(const _uint&);
  const _uint& operator-=(const _uint&);
  const _uint& operator*=(const _uint&);
  const _uint& operator/=(const _uint&);
  const _uint& operator%=(const _uint&);
  const _uint& operator&=(const _uint&);
  const _uint& operator^=(const _uint&);
  const _uint& operator|=(const _uint&);
  const _uint operator~() const;
  template <typename mvT> const _uint& operator<<=(const mvT&);
  template <typename mvT> const _uint& operator>>=(const mvT&);

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
_uint<HeadT, TailT>::_uint()
  : _head(0)
  , _tail(0) {}

template <typename HeadT, typename TailT>
_uint<HeadT, TailT>::_uint(const HeadT& h, const TailT& t)
  : _head(h)
  , _tail(t) {}

template <typename HeadT, typename TailT>
template <typename other_uint>
_uint<HeadT, TailT>::_uint(const other_uint& num)
  : _head(bits_size_of<TailT>() < bits_size_of<other_uint>() ?
      num >> bits_size_of<TailT>() : 0)
  , _tail(num) {}

template <typename HeadT, typename TailT>
_uint<HeadT, TailT>::_uint(const std::string& str, const uint8_t base)
  : _head(0)
  , _tail(0) {
  _uint<HeadT, TailT> digit(1);
  for (auto iter = str.rbegin(); iter != str.rend(); ++iter) {
    *this += (digit * _uint<HeadT, TailT>(*iter - '0'));
    digit *= base;
  }
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator=(const _uint& num) {
  _head = num._head;
  _tail = num._tail;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator++() {
  const auto tmp = _tail;
  ++_tail;
  if (_tail < tmp) {
    ++_head;
  }
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
  const auto tmp = _tail;
  --_tail;
  if (_tail > tmp) {
    --_head;
  }
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator--(int) {
  const _uint<HeadT, TailT> res(*this);
  --(*this);
  return res;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator+=(const _uint& num) {
  const TailT tail_sum = _tail + num._tail;
  if (tail_sum < _tail) {
    ++_head;
  }
  _head += num._head;
  _tail = tail_sum;
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator-=(const _uint& num) {
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
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator*=(const _uint& num) {
  _uint<HeadT, TailT> base(num);
  _uint<HeadT, TailT> tmp(*this);
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
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator/=(const _uint& num) {
  if (num == 0) {
    throw std::runtime_error::runtime_error("division by zero");
  }
  _uint<HeadT, TailT> base(num);
  _uint<HeadT, TailT> digit_bit(1);
  _uint<HeadT, TailT> tmp(*this);
  *this = 0;
  if (tmp >= base) {
    ssize_t k = bits_size_of(*this) - bits_len(base);
    digit_bit <<= k;
    base <<= k;
    while (tmp >= num) {
      // std::cout << "000" << std::endl;
      if (base <= tmp) {
        tmp -= base;
        *this ^= digit_bit;
      }
      digit_bit >>= 1;
      base >>= 1;
    }
  }
  return *this;
}

template <typename HeadT, typename TailT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator%=(const _uint& num) {
  return (*this -= ((*this / num) * num));
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
const _uint<HeadT, TailT> _uint<HeadT, TailT>::operator~() const {
  _uint<HeadT, TailT> res(*this);
  res._head = ~(res._head);
  res._tail = ~(res._tail);
  return res;
}

template <typename HeadT, typename TailT>
template <typename mvT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator<<=(const mvT& num) {
  const std::size_t _num = num;
  _head <<= _num;
  _head ^= HeadT(_tail >> (bits_size_of<TailT>() - _num));
  _tail <<= _num;
  return *this;
}

template <typename HeadT, typename TailT>
template <typename mvT>
const _uint<HeadT, TailT>& _uint<HeadT, TailT>::operator>>=(const mvT& num) {
  const std::size_t _num = num;
  const auto tmp = *this;
  _tail >>= _num;
  _tail ^= (TailT(_head) << (bits_size_of<TailT>() - _num));
  _head >>= _num;
  return *this;
}

}  // namespace pkr
