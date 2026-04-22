#pragma once

#include "../../../math/iroot/sqrt/lib.hpp"
#include "../../../math/qpow/mod/lib.hpp"
#include "../../../util/alias/others/lib.hpp"

namespace tifa_libs {

class bsgs_fix {
  u64 p;
  vecuu dlg;

 public:
  void init(u32 g, u64 p) NE {
    const u32 L = isqrt(this->p = p) + 1, B = isqrt(p * L * 2 / ((u64)std::bit_width(p) * 3));
    hmap<u64, u64> hmp;
    u64 s = 1;
    flt_ (u32, i, 0, B) {
      if (hmp.find(s) != hmp.end()) break;
      hmp[s] = i, s = mul_mod_u(s, g, p);
    }
    const u64 inv = qpow_mod(g, p - 1 - B, p);
    auto calc = [&](u32 x) -> u64 {
      u64 s = x;
      flt_ (u32, i, 0, u32(p / B + 1)) {
        if (hmp.find(s) != hmp.end()) {
          retif_((auto ret = mul_mod_u(i, B, p - 1) + hmp[s]; ret >= p - 1), ret - p + 1, ret);
        }
        s = mul_mod_u(s, inv, p);
      }
      return -1_u64;
    };
    vecb vis(L + 1);
    vecu ps;
    // clang-format off
    ps.reserve((usz)max(127, int(L * (L >= 2e5 ? 1.6 : 1.7) / std::bit_width(L) + 1))), dlg.resize(L + 1);
    // clang-format on
    flt_ (u32, i, 2, L + 1) {
      if (!vis[i]) ps.push_back(i), dlg[i] = calc(i);
      for (auto p : ps) {
        if ((u64)i * p > L) break;
        if (vis[i* p] = true; (dlg[i * p] = dlg[i] + dlg[p]) >= this->p - 1) dlg[i * p] -= this->p - 1;
        if (!(i % p)) break;
      }
    }
  }

  // solve $g^x\equiv b \pmod p$
  CEXP u64 operator()(u64 b) CNE {
    if (b < dlg.size()) return dlg[b];
    u64 ret;
    if (u64 v = p / b, r = p % b; r < b - r) {
      if (ret = operator()(r) - dlg[v] + (p - 1) / 2; (i64)ret < 0) ret += p - 1;
    } else ret = operator()(b - r) + p - 1 - dlg[v + 1];
    retif_((ret >= p - 1), ret - p + 1, ret);
  }
};

}  // namespace tifa_libs
