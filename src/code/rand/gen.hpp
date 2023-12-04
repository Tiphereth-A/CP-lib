#ifndef TIFALIBS_RAND_GEN
#define TIFALIBS_RAND_GEN

#include "../util/util.hpp"

namespace tifa_libs::rand {

template <class Distri>
class Gen {
  std::conditional_t<sizeof(typename Distri::result_type) <= 4, std::mt19937, std::mt19937_64> re;
  Distri dist;

 public:
  using random_engine = decltype(re);
  using distribution = Distri;
  using result_type = typename Distri::result_type;

  Gen() : re(std::random_device{}()), dist() {}
  Gen(result_type a, result_type b) : re(std::random_device{}()), dist(a, b) {}

  void set_range(result_type a, result_type b) { dist = Distri(a, b); }
  random_engine& rand_eng() { return re; }
  Distri& distrib() { return dist; }

  result_type operator()() { return dist(re); }
};

}  // namespace tifa_libs::rand

#endif