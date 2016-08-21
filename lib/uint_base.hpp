#pragma once
#pragma GCC diagnostic ignored "-Wshift-count-overflow"

#include <cstddef>
#include <stdexcept>
#include <string>
#include "uint.hpp"
#include "util.hpp"

namespace pkr {

template <typename HeadT, typename TailT>
class Uint {
public:
  constexpr Uint() = default;
  constexpr Uint(const Uint&) = default;
  constexpr Uint(const HeadT&, const TailT&) noexcept;
  Uint(const std::string&, const uint8_t = 10) noexcept;
  template <typename OtherUint> constexpr Uint(const OtherUint&) noexcept;

  constexpr Uint operator++(int) noexcept;
  constexpr Uint operator--(int) noexcept;
  constexpr Uint& operator++() noexcept;
  constexpr Uint& operator--() noexcept;
  constexpr Uint& operator= (const Uint&) noexcept;
  constexpr Uint& operator+=(const Uint&) noexcept;
  constexpr Uint& operator-=(const Uint&) noexcept;
  constexpr Uint& operator*=(const Uint&) noexcept;
  constexpr Uint& operator/=(const Uint&);
  constexpr Uint& operator%=(const Uint&) noexcept;
  constexpr Uint& operator&=(const Uint&) noexcept;
  constexpr Uint& operator^=(const Uint&) noexcept;
  constexpr Uint& operator|=(const Uint&) noexcept;
  constexpr Uint& operator<<=(uint32_t) noexcept;
  constexpr Uint& operator>>=(uint32_t) noexcept;

  inline explicit constexpr operator bool() const noexcept {
    return (_head || _tail);
  }

  inline explicit constexpr operator uint8_t() const noexcept {
    return static_cast<uint8_t>(_tail);
  }

  inline explicit constexpr operator uint16_t() const noexcept {
    if (tail_sz < 16) {
      return ((static_cast<uint16_t>(_head) << tail_sz)
        + static_cast<uint16_t>(_tail));
    } else {
      return static_cast<uint16_t>(_tail);
    }
  }

  inline explicit constexpr operator uint32_t() const noexcept {
    if (tail_sz < 32) {
      return ((static_cast<uint32_t>(_head) << tail_sz)
        + static_cast<uint32_t>(_tail));
    } else {
      return static_cast<uint32_t>(_tail);
    }
  }

  inline explicit constexpr operator uint64_t() const noexcept {
    if (tail_sz < 64) {
      return ((static_cast<uint64_t>(_head) << tail_sz)
        + static_cast<uint64_t>(_tail));
    } else {
      return static_cast<uint64_t>(_tail);
    }
  }

  inline constexpr HeadT head() const noexcept {
    return _head;
  }

  inline constexpr TailT tail() const noexcept {
    return _tail;
  }

private:
  HeadT _head{0};
  TailT _tail{0};

  static constexpr auto tail_sz{util::bits_size_of<TailT>()};
  static constexpr auto head_sz{util::bits_size_of<HeadT>()};
};

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>::Uint(const HeadT& h, const TailT& t) noexcept
  : _head(h)
  , _tail(t) {}

template <typename HeadT, typename TailT>
template <typename OtherUint> constexpr
Uint<HeadT, TailT>::Uint(const OtherUint& num) noexcept
  : _head(tail_sz < util::bits_size_of<OtherUint>() ? num >> tail_sz : 0)
  , _tail(num) {}

template <typename HeadT, typename TailT>
Uint<HeadT, TailT>::Uint(const std::string& str, const uint8_t base) noexcept {
  Uint<HeadT, TailT> digit(1);
  for (auto iter = str.crbegin(); iter != str.crend(); ++iter) {
    *this += (digit * Uint<HeadT, TailT>(*iter - '0'));
    digit *= base;
  }
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator=(const Uint& num) noexcept {
  _head = num._head;
  _tail = num._tail;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator++() noexcept {
  const auto tmp = _tail;
  ++_tail;
  if (_tail < tmp) {
    ++_head;
  }
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT> Uint<HeadT, TailT>::operator++(int) noexcept {
  const Uint<HeadT, TailT> res(*this);
  ++(*this);
  return res;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator--() noexcept {
  // TODO. optimize: if ~tail == 0 -> --head (same with ++)
  const auto tmp = _tail;
  --_tail;
  if (_tail > tmp) {
    --_head;
  }
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT> Uint<HeadT, TailT>::operator--(int) noexcept {
  const Uint<HeadT, TailT> res(*this);
  --(*this);
  return res;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator+=(const Uint& num) noexcept {
  const TailT tail_sum = _tail + num._tail;
  if (tail_sum < _tail) {
    ++_head;
  }
  _head += num._head;
  _tail = tail_sum;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator-=(const Uint& num) noexcept {
  if (_tail < num._tail) {
    --_head;
  }
  _head -= num._head;
  _tail -= num._tail;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator*=(const Uint& num) noexcept {
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

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator/=(const Uint& num) {
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

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator%=(const Uint& num) noexcept {
  return *this -= ((*this / num) * num);
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator&=(const Uint& num) noexcept {
  _head &= num._head;
  _tail &= num._tail;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator|=(const Uint& num) noexcept {
  _head |= num._head;
  _tail |= num._tail;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator^=(const Uint& num) noexcept {
  _head ^= num._head;
  _tail ^= num._tail;
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator<<=(uint32_t num) noexcept {
  if (num <= 8) {
    _head <<= num;
    _head ^= HeadT(_tail >> (tail_sz - num));
    _tail <<= num;
  } else {
    *this <<= 8;
    *this <<= (num - 8);
  }
  return *this;
}

template <typename HeadT, typename TailT> constexpr
Uint<HeadT, TailT>& Uint<HeadT, TailT>::operator>>=(uint32_t num) noexcept {
  if (num <= 8) {
    _tail >>= num;
    _tail ^= (TailT(_head) << (tail_sz - num));
    _head >>= num;
  } else {
    *this >>= 8;
    *this >>= (num - 8);
  }
  return *this;
}

}  // namespace pkr
