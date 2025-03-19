#ifndef TIFALIBS_UTIL_TRAITS_GRAPH
#define TIFALIBS_UTIL_TRAITS_GRAPH
// clang-format off
#include "consts.hpp"

namespace tifa_libs {

//! weighted or unweighted
template <class T> concept sparse_graph_c = requires(T g) { g.cnt_arc; g.deg_in; g.deg_out; g.size(); g.foreach(0, fn_0); } && (requires(T g) { g.add_arc(0, 0); g.add_edge(0, 0); } || requires(T g) { g.add_arc(0, 0, {}); g.add_edge(0, 0, {}); });
//! weighted or unweighted
template <class T> concept alist_c = sparse_graph_c<T> && requires(T g) { {g[0]} -> common_range; g.build(); };
//! weighted or unweighted
template <class T> concept eog_c = sparse_graph_c<T> && requires(T g) { g.head; g.e; g.pop_startwith(0); };
//! weighted or unweighted
template <class T> concept tree_c = alist_c<T> && requires(T g) { g.root; };
// weighted
template <class T> concept sparse_graphw_c = sparse_graph_c<T> && !std::is_void_v<TPN T::w_t> && requires(T g, TPN T::w_t w) { g.add_arc(0, 0, w); g.add_edge(0, 0, w); };
// weighted
template <class T> concept alistw_c = alist_c<T> && sparse_graphw_c<T> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
// weighted
template <class T> concept eogw_c = eog_c<T> && sparse_graphw_c<T> && requires(T g) { g[0].to; g[0].w; g[0].nxt; };
// weighted
template <class T> concept treew_c = tree_c<T> && alistw_c<T>;

}  // namespace tifa_libs
// clang-format on
#endif