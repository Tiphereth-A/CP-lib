#ifndef TIFALIBS_ENUM_ENUM_SUBSET
#define TIFALIBS_ENUM_ENUM_SUBSET

#include "../util/alias_num.hpp"

namespace tifa_libs {

// enumerate x : $\varnothing\ne x \subset b$
template <u32 = 0>
class enum_subset {
  static inline u32 b_;
  u32 now_;

  static CEXP u32 num_begin() NE { return b_; }
  static CEXP u32 num_end() NE { return 0; }

 public:
  static CEXP void set(u32 b) NE { b_ = b; }
  static CEXP enum_subset begin() NE { return num_begin(); }
  static CEXP enum_subset end() NE { return num_end(); }

  CEXP enum_subset(u32 now = num_begin()) NE : now_(now) { assert(now <= num_begin()); }

  CEXP u32 operator*() CNE { return now_; }
  CEXP bool operator!=(enum_subset CR x) CNE { return **this != *x; }
  CEXP void operator++() NE { now_ = (now_ - 1) & b_; }
};

}  // namespace tifa_libs

#endif