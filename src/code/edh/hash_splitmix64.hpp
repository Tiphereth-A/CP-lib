#ifndef TIFALIBS_EDH_HASH_SPLITMIX64
#define TIFALIBS_EDH_HASH_SPLITMIX64

#include "../util/traits.hpp"

namespace tifa_libs {

class hash_splitmix64 {
  static inline u64 seed = 114514;
  static CEXP u64 splitmix64(u64 x) { return x += 0x9e3779b97f4a7c15, x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9, x = (x ^ (x >> 27)) * 0x94d049bb133111eb, x ^ (x >> 31); }
  static CEXP u64 append(u64 x, u64 y) { return x ^ (y >> 1) ^ ((y & 1) << 63); }

 public:
  explicit hash_splitmix64() { set_seed(); }
  CEXPE hash_splitmix64(u64 s) { set_seed(s); }

  static void set_seed() { seed = (u64)std::chrono::steady_clock::now().time_since_epoch().count(); }
  static CEXP void set_seed(u64 s) { seed = s; }
  u64 operator()(u64 x) const { return splitmix64(x + seed); }
  template <class T, class U>
  u64 operator()(std::pair<T, U> CR p) const { return append((*this)(p.first), (*this)(p.second)); }
  template <class... Ts>
  u64 operator()(std::tuple<Ts...> CR tp) const {
    u64 ret = 0;
    std::apply([&](Ts CR... targs) { ((ret = append(ret, (*this)(targs))), ...); }, tp);
    return ret;
  }
  template <iterable_c T>
  u64 operator()(T CR tp) const {
    u64 ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};

}  // namespace tifa_libs

#endif