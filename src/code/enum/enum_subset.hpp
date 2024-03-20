#ifndef TIFALIBS_ENUM_ENUM_SUBSET
#define TIFALIBS_ENUM_ENUM_SUBSET

#include "../util/util.hpp"

namespace tifa_libs {

// enumerate x : \varnothing\ne x \subset b
template <u32 = 0>
class enum_subset {
  static inline u32 b_;
  u32 now_;

  static constexpr u32 num_begin() { return b_; }
  static constexpr u32 num_end() { return 0; }

 public:
  static constexpr void set(u32 b) { b_ = b; }
  static constexpr enum_subset begin() { return num_begin(); }
  static constexpr enum_subset end() { return num_end(); }

  constexpr enum_subset(u32 now = num_begin()) : now_(now) { assert(now <= num_begin()); }

  constexpr u32 operator*() const { return now_; }
  constexpr bool operator!=(enum_subset const& x) const { return **this != *x; }
  constexpr void operator++() { now_ = (now_ - 1) & b_; }
};

}  // namespace tifa_libs

#endif