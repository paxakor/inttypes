#pragma once

#include "inttypes_base.hpp"

typedef _uint<uint8_t,  uint16_t> uint24_t;
typedef _uint<uint8_t,  uint32_t> uint40_t;
typedef _uint<uint16_t, uint32_t> uint48_t;
typedef _uint<uint8_t,  uint48_t> uint56_t;
typedef _uint<uint8_t,  uint64_t> uint72_t;
typedef _uint<uint16_t, uint64_t> uint80_t;
typedef _uint<uint8_t,  uint80_t> uint88_t;
typedef _uint<uint32_t, uint64_t> uint96_t;
typedef _uint<uint40_t, uint64_t> uint104_t;
typedef _uint<uint48_t, uint64_t> uint112_t;
typedef _uint<uint56_t, uint64_t> uint120_t;
