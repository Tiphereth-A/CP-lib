#ifndef TIFALIBS_COMB_BALL_BOX_DDL
#define TIFALIBS_COMB_BALL_BOX_DDL

#include "binom.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

template <class mint, class fact>
CEXP mint ball_box_ddl(u32, u32 box, spnuu pows, binom<mint, fact> CR b) NE {
  mint ans = 0;
  bool f = box & 1;
  flt_ (u32, i, 1, box + 1) {
    auto _ = b.mCn(box, i) * pows[i];
    f ? ans += _ : ans -= _;
    f ^= 1;
  }
  return ans;
}
template <class mint, class fact>
CEXP mint ball_box_ddl(u32 ball, u32 box, binom<mint, fact> CR b) NE { return ball_box_ddl<mint>(ball, box, gen_pows(box + 1, ball, mint::mod()), b); }

}  // namespace tifa_libs::math

#endif