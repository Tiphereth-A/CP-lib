#ifndef TIFA_LIBS_UTIL_SIMULATED_ANNEALING
#define TIFA_LIBS_UTIL_SIMULATED_ANNEALING

#include "gen.hpp"

namespace tifa_libs::rand {

template <class T, class Re, class fT = double, class Tt = double>
class simuanl {
  const Tt Tmax, Tmin, dT;
  using Distri = std::uniform_real_distribution<Tt>;
  Gen<Re, Distri> g;

  //? Metropolis acceptance criteria
  bool chk(fT dfit, Tt now_T) { return dfit <= 0 || std::exp(-dfit / now_T) > g(); }

 public:
  explicit simuanl(Re &&re, Tt Tmax = 1e10, Tt Tmin = 1e-10, Tt dT = 1 - 1e-5) : Tmax(Tmax), Tmin(Tmin), dT(dT), g(re, Distri(0, 1)) {}

  // Find minimum for fitness(sequence), which sequence is a permutation of initial_sequence
  // F: fT(vec<T> const &)
  template <class F>
  std::pair<fT, vec<T>> sa_seq(vec<T> const &seq, F fit) {
    std::uniform_int_distribution<size_t> u_idx(0, seq.size());
    vec<T> ans_seq = seq;
    fT ans = fit(ans_seq);
    for (Tt t = Tmax; t > Tmin; t *= dT) {
      size_t x, y;
      do {
        x = u_idx(g.rand_eng()), y = u_idx(g.rand_eng());
      } while (x == y);
      std::swap(ans_seq[x], ans_seq[y]);
      if (fT now_ans = fit(ans_seq); chk(now_ans - ans, t)) ans = now_ans;
      else std::swap(ans_seq[x], ans_seq[y]);
    }
    return {ans, ans_seq};
  }
  // Find minimum for fitness(sequence), which sequence[i] in [minimum[i], maximum[i]]
  // F: fT(vec<T> const &)
  template <class F>
  std::pair<fT, vec<T>> sa_range(vec<T> const &mini, vec<T> const &maxi, F fit) {
    assert(mini.size() == maxi.size());
    auto new_ = [&, this]() -> vec<T> {
      vec<T> ret;
      for (auto i = mini.begin(), j = maxi.begin(); i != mini.end(); ++i, ++j) ret.push_back(std::uniform_int_distribution<T>(*i, *j)(g.rand_eng()));
      return ret;
    };
    vec<T> ans_seq(new_()), now_seq;
    fT ans = fit(ans_seq);
    for (Tt t = Tmax; t > Tmin; t *= dT) {
      now_seq = new_();
      if (fT now_ans = fit(now_seq); chk(now_ans - ans, t)) {
        ans = now_ans;
        ans_seq = now_seq;
      }
    }
    return {ans, ans_seq};
  }
};

}  // namespace tifa_libs::rand

#endif