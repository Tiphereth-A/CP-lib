// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

#define for_(i, l, r, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define fors_(i, l, r, s, ...) for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define rfor_(i, r, l, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; --i)
#define rfors_(i, r, l, s, ...) for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)

template <class... T>
void inc(T &...x) { ((++x), ...); }
template <class... T>
void debug([[maybe_unused]] T const &...args) {
#ifdef LOCAL_
  size_t n = 0;
  ((cerr << args << (++n != sizeof...(T) ? " " : "\n")), ...);
#endif
}
// __PRETTY_FUNCTION__ can be replaced by
// std::source_location::current().function_name()
#define dbgl_ (cerr << __LINE__ << ' ' << __PRETTY_FUNCTION__ << endl)

// #define MCAS
void solve(int) {
}

signed main() {
#ifdef LOCAL_
  auto ST_ = chrono::high_resolution_clock::now();
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
#ifdef MCAS
  int t_ = 0;
  cin >> t_;
  for (i_ = 0; i_ < t_; ++i_)
#endif
    debug("Case", i_), solve(i_);
#ifdef LOCAL_
  auto ED_ = chrono::high_resolution_clock::now();
  clog << "\n---\n"
       << chrono::duration_cast<chrono::nanoseconds>(ED_ - ST_).count() * 1e-6l << " ms" << endl;
#endif
  return 0;
}