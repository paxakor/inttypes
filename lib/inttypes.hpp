#pragma once

#include "uint.hpp"

namespace pkr {

using uint24_t   = Uint<uint8_t,  uint16_t>;
using uint40_t   = Uint<uint8_t,  uint32_t>;
using uint48_t   = Uint<uint16_t, uint32_t>;
using uint56_t   = Uint<uint8_t,  uint48_t>;
using uint72_t   = Uint<uint8_t,  uint64_t>;
using uint80_t   = Uint<uint16_t, uint64_t>;
using uint88_t   = Uint<uint8_t,  uint80_t>;
using uint96_t   = Uint<uint32_t, uint64_t>;
using uint104_t  = Uint<uint40_t, uint64_t>;
using uint128_t  = Uint<uint64_t, uint64_t>;
using uint256_t  = Uint<uint128_t, uint128_t>;
using uint512_t  = Uint<uint256_t, uint256_t>;
using uint1024_t = Uint<uint512_t, uint512_t>;

}  // namespace pkr
