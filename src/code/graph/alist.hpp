#ifndef TIFALIBS_GRAPH_ALIST
#define TIFALIBS_GRAPH_ALIST

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <bool with_deg = false>
struct alist {
  using weight_type = u32;
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in;

  //! vertex ID: [0, n)
  explicit CEXP alist(u32 n = 0) : g(n), cnt_arc(0), deg_in(0) {
    if CEXP (with_deg) deg_in.resize(n);
  }

  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v];
  }
};
template <class G>
concept is_alist = (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);

}  // namespace tifa_libs::graph

#endif