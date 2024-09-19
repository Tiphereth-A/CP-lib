#ifndef TIFALIBS_RAND_GEN
#define TIFALIBS_RAND_GEN

#include "../util/util.hpp"

namespace tifa_libs::rand {

template <class Distri>
class Gen {
  std::conditional_t<sizeof(TPN Distri::result_type) <= 4, std::mt19937, std::mt19937_64> re;
  Distri dist;

 public:
  using random_engine = decltype(re);
  using distribution = Distri;
  using res_t = TPN Distri::result_type;

  CEXP Gen() : re(std::random_device{}()), dist() {}
  CEXP Gen(res_t a, res_t b) : re(std::random_device{}()), dist(a, b) {}

  CEXP void set_range(res_t a, res_t b) { dist = Distri(a, b); }
  CEXP random_engine& rand_eng() { return re; }
  CEXP Distri& distrib() { return dist; }
  void reset_seed() { re.seed((res_t)std::chrono::duration_cast<std::conditional_t<sizeof(res_t) <= 4, std::chrono::seconds, std::chrono::nanoseconds>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()); }
  CEXP res_t operator()() { return dist(re); }
  res_t next() { return dist(re); }
};

}  // namespace tifa_libs::rand

#endif