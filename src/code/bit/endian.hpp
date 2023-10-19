#ifndef TIFA_LIBS_BIT_ENDIAN
#define TIFA_LIBS_BIT_ENDIAN

namespace tifa_libs::bit {

// From GCC lib
enum class endian {
  little = __ORDER_LITTLE_ENDIAN__,
  big = __ORDER_BIG_ENDIAN__,
  native = __BYTE_ORDER__
};

}  // namespace tifa_libs::bit

#endif