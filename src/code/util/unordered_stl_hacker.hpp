#ifndef TIFA_LIBS_UTIL_UNORDERED_STL_HACKER
#define TIFA_LIBS_UTIL_UNORDERED_STL_HACKER

#include "../rand/gen.hpp"
#include "util.hpp"

namespace tifa_libs::util {

// Just run it on the same compiler and same options as the solution you want to hack.
// Works for integral types, and std::string. Slow for std::string.
template <class T>
vec<T> unordered_stl_hacker(usz n) {
  auto get_bucket_counts = [n]() {
    vec<usz> ans;
    std::unordered_set<int> s;
    rand::Gen<std::uniform_int_distribution<int>> gen;

    while (s.size() < n) {
      if (ans.empty() || ans.back() != s.bucket_count()) ans.push_back(s.bucket_count());
      s.insert(gen());
    }
    return ans;
  };

  vec<usz> bc = get_bucket_counts();

  if constexpr (std::is_same_v<std::string, T>) {
    // Edit these if need
    const usz len = 15;
    const std::string pref = "";
    const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";

    rand::Gen<std::uniform_int_distribution<usz>> gen(0, alphabet.size() - 1);
    auto gen_str_with_divisible_hash = [&](usz mod) -> std::string {
      std::string s = pref;
      while (true) {
        s.resize(pref.size());
        while (s.size() < len) s += alphabet[gen()];
        if (!(std::hash<std::string>{}(s) % mod)) return s;
      }
      return "";
    };
    vec<T> ans1;
    i64 op1 = 0;
    for (usz i = 0, psb = 0, cnt = 0, lst = bc[0]; i < n; ++i) {
      T nw = gen_str_with_divisible_hash(lst);
      ans1.push_back(nw);
      op1 += cnt;
      if (i >= lst) {
        lst = bc[++psb];
        cnt = 1;
      } else ++cnt;
    }
    vec<T> ans2;
    i64 op2 = 0;
    for (usz i = 0, cnt = 0, pr = bc.size() > 1 ? bc[bc.size() - 2] : 0, lst = bc.back(); i < n; ++i) {
      T nw = gen_str_with_divisible_hash(lst);
      ans2.push_back(nw);
      op2 += i < pr ? 1 : cnt;
      ++cnt;
    }
    return op1 > op2 ? ans1 : ans2;
  } else if constexpr (std::is_integral_v<T>) {
    vec<T> ans1;
    i64 op1 = 0;
    for (usz i = 0, psb = 0, cnt = 0, lst = bc[0]; i < n; ++i) {
      ans1.push_back(T(lst * cnt));
      op1 += cnt;
      if (i >= lst) {
        lst = bc[++psb];
        cnt = 1;
      } else ++cnt;
    }
    vec<T> ans2;
    i64 op2 = 0;
    for (usz i = 0, cnt = 0, pr = bc.size() > 1 ? bc[bc.size() - 2] : 0, lst = bc.back(); i < n; ++i) {
      ans2.push_back(T(lst * cnt));
      op2 += i < pr ? 1 : cnt;
      ++cnt;
    }
    return op1 > op2 ? ans1 : ans2;
  }
}

}  // namespace tifa_libs::util

#endif