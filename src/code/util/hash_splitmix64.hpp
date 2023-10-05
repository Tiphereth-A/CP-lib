#ifndef TIFA_LIBS_UTIL_HASH_SPLITMIX64
#define TIFA_LIBS_UTIL_HASH_SPLITMIX64

#include "util.hpp"

namespace tifa_libs::util {

class hash_splitmix64 {
  static inline u64 seed;
  static constexpr uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static constexpr size_t append(size_t x, size_t y) { return x ^ (y >> 1) ^ ((y & 1) << (sizeof(size_t) * 8 - 1)); }

 public:
  explicit hash_splitmix64() {}

  static constexpr void set_seed(u64 s) { seed = s; }
  size_t operator()(uint64_t x) const { return splitmix64(x + seed); }

  template <class Tp, class Up>
  size_t operator()(std::pair<Tp, Up> const &p) const { return append((*this)(p.first), (*this)(p.second)); }
  template <typename... Ts>
  size_t operator()(std::tuple<Ts...> const &tp) const {
    size_t ret = 0;
    std::apply([&](Ts const &...targs) { ((ret = append(ret, (*this)(targs))), ...); }, tp);
    return ret;
  }
  template <class Tp, std::enable_if_t<std::is_same_v<decltype(std::declval<Tp>().begin()), typename Tp::iterator>> * = nullptr>
  size_t operator()(Tp const &tp) const {
    size_t ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};
template <class Tp, class Hash = hash_splitmix64>
using hset = std::unordered_set<Tp, Hash>;
template <class Key, class Tp, class Hash = hash_splitmix64>
using hmap = std::unordered_map<Key, Tp, Hash>;

}  // namespace tifa_libs::util

#endif