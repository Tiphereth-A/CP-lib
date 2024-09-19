#ifndef TIFALIBS_ENUM_ENUM_SUBSET
#define TIFALIBS_ENUM_ENUM_SUBSET

#include "../util/util.hpp"

namespace tifa_libs {

// enumerate x : $\varnothing\ne x \subset b$
template <u32 = 0>
class enum_subset {
  static inline u32 b_;
  u32 now_;

  static CEXP u32 num_begin() { return b_; }
  static CEXP u32 num_end() { return 0; }

 public:
  static CEXP void set(u32 b) { b_ = b; }
  static CEXP enum_subset begin() { return num_begin(); }
  static CEXP enum_subset end() { return num_end(); }

  CEXP enum_subset(u32 now = num_begin()) : now_(now) { assert(now <= num_begin()); }

  CEXP u32 operator*() const { return now_; }
  CEXP bool operator!=(enum_subset CR x) const { return **this != *x; }
  CEXP void operator++() { now_ = (now_ - 1) & b_; }
};

}  // namespace tifa_libs

#endif