#ifndef TIFA_LIBS_MATH_XOR_BASIS
#define TIFA_LIBS_MATH_XOR_BASIS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::size_t N = 64>
class basis_Z2 {
  vec<std::bitset<N>> base;

 public:
  constexpr basis_Z2() {}

  constexpr std::bitset<N> &operator[](size_t index) { return base[index]; }
  constexpr std::bitset<N> operator[](size_t index) const { return base[index]; }
  constexpr vec<std::bitset<N>> &data() { return base; }
  constexpr vec<std::bitset<N>> data() const { return base; }

  constexpr size_t rank() const {
    size_t res = 0;
    for (size_t i = 0; i < base.size(); ++i) res += base[i][i];
    return res;
  }

  constexpr bool insert(std::bitset<N> x) {
    bool status = false;
    for (size_t i = base.size() - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (base[i][i])
        x ^= base[i];
      else {
        for (size_t j = 0; j < i; ++j)
          if (x[j]) x ^= base[j];
        for (size_t j = i + 1; j < base.size(); ++j)
          if (base[j][i]) base[j] ^= x;
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }
  constexpr std::bitset<N> max_span() const {
    std::bitset<N> ret;
    for (auto &&i : base) ret ^= i;
    return ret;
  }

  // @return std::nullopt if x is linear independent with current basis, else return the solution
  constexpr std::optional<std::bitset<N>> coord(std::bitset<N> x) {
    std::bitset<N> res;
    for (size_t i = base.size() - 1; ~i; --i)
      if (x[i]) {
        if (!base[i][i]) return {};
        res.set(i);
        x ^= base[i];
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif