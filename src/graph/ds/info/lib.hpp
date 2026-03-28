#pragma once

#include "../graph_c/lib.hpp"

namespace tifa_libs {
struct arc_cnt_tag : graph_info_impl_::graph_info_tag_base {
  CEXPE arc_cnt_tag(u32) NE : ecnt{0} {}

  CEXP u32 esize() CNE { return ecnt; }

 protected:
  u32 ecnt;
  CEXP void add_arc(u32, u32, auto...) NE { ++ecnt; }
  CEXP void del_arc(u32, u32, auto...) NE { --ecnt; }
};
template <class T>
struct vweight_tag : graph_info_impl_::graph_info_tag_base {
  vec<T> vw;
  CEXPE vweight_tag(u32 n) NE : vw(n) {}

 protected:
  CEXP void add_arc(u32, u32, auto...) NE {}
  CEXP void del_arc(u32, u32, auto...) NE {}
};
struct degin_tag : graph_info_impl_::graph_info_tag_base {
  vecu din;
  CEXPE degin_tag(u32 n) NE : din(n) {}

 protected:
  CEXP void add_arc(u32, u32 v, auto...) NE { ++din[v]; }
  CEXP void del_arc(u32, u32 v, auto...) NE { --din[v]; }
};
struct degout_tag : graph_info_impl_::graph_info_tag_base {
  vecu dout;
  CEXPE degout_tag(u32 n) NE : dout(n) {}

  CEXP u32 deg_out(u32 u) CNE { return dout[u]; }

 protected:
  CEXP void add_arc(u32 u, u32, auto...) NE { ++dout[u]; }
  CEXP void del_arc(u32 u, u32, auto...) NE { --dout[u]; }
};
}  // namespace tifa_libs
