#ifndef TIFALIBS_ENUM_ENUM_SUPSET
#define TIFALIBS_ENUM_ENUM_SUPSET

#include "../util/util.hpp"

namespace tifa_libs {

// enumerate x : $b \subset x \subset n$
template <u32 = 0>
class enum_supset {
  static inline u32 b_, n_;
  u32 now_;

  static CEXP u32 num_begin() NE { return b_; }
  static CEXP u32 num_end() NE { return 1_u32 << n_; }

 public:
  static CEXP void set(u32 b, u32 n) NE {
    assert((u32)std::countl_one(b) <= n && n < 32);
    b_ = b, n_ = n;
  }
  static CEXP enum_supset begin() NE { return num_begin(); }
  static CEXP enum_supset end() NE { return num_end(); }

  CEXP enum_supset(u32 now = num_begin()) NE : now_(now) { assert(now <= num_end()); }

  CEXP u32 operator*() CNE { return now_; }
  CEXP bool operator!=(enum_supset CR x) CNE { return **this != *x; }
  CEXP void operator++() NE { now_ = min((now_ + 1) | b_, num_end()); }
};

}  // namespace tifa_libs

#endif