#ifndef TIFA_LIBS_UTIL_RAND_GEN
#define TIFA_LIBS_UTIL_RAND_GEN

#include "../util/util.hpp"

namespace tifa_libs::rand {

template <class Re, class Distri>
class Gen {
  Re re;
  Distri dist;

public:
  using random_engine = Re;
  using distribution = Distri;
  using result_type = typename Distri::result_type;

  Gen(Re &&re_, Distri &&dist_):
    re(std::move(re_)), dist(std::move(dist_)) {}

  Re &rand_eng() { return re; }
  Re rand_eng() const { return re; }
  Distri &distrib() { return dist; }
  Distri distrib() const { return dist; }

  result_type operator()() { return dist(re); }
};

}  // namespace tifa_libs::rand

#endif