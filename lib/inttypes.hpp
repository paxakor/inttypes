#pragma once

#include "uint.hpp"

namespace pkr {

typedef Uint<uint8_t,  uint16_t> uint24_t;
typedef Uint<uint8_t,  uint32_t> uint40_t;
typedef Uint<uint16_t, uint32_t> uint48_t;
typedef Uint<uint8_t,  uint48_t> uint56_t;
typedef Uint<uint8_t,  uint64_t> uint72_t;
typedef Uint<uint16_t, uint64_t> uint80_t;
typedef Uint<uint8_t,  uint80_t> uint88_t;
typedef Uint<uint32_t, uint64_t> uint96_t;
typedef Uint<uint40_t, uint64_t> uint104_t;
typedef Uint<uint64_t, uint64_t> uint128_t;
typedef Uint<uint128_t, uint128_t> uint256_t;
typedef Uint<uint256_t, uint256_t> uint512_t;
typedef Uint<uint512_t, uint512_t> uint1024_t;

}  // namespace pkr
