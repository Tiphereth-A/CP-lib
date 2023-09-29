#ifndef TIFA_LIBS_BIT_ROTL
#define TIFA_LIBS_BIT_ROTL

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr T rotl(T x, int s) {
  constexpr int nd = sizeof(T) * 8;
  if constexpr ((nd & (nd - 1)) == 0) {
    constexpr unsigned und = nd;
    const unsigned r = (unsigned)s;
    return (x << (r % und)) | (x >> ((-r) % und));
  }
  if (const int r = s % nd; r == 0)
    return x;
  else if (r > 0)
    return (x << r) | (x >> ((nd - r) % nd));
  else
    return (x >> -r) | (x << ((nd + r) % nd));
}

}  // namespace tifa_libs::bit

#endif