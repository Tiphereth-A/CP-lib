#ifndef TIFALIBS_TREE_BTREE_MAKE_POST_PI
#define TIFALIBS_TREE_BTREE_MAKE_POST_PI

#include "../util/util.hpp"

namespace tifa_libs::graph {

namespace btree_make_post_pi_impl_ {
constexpr void dfs(vecu const& pre, vecu const& in, vecu& post, u32& p, u32 l, u32 r) {
  if (l >= r) return;
  u32 rt = pre[p++];
  u32 m = -1_u32;
  for (u32 i = l; i < r; ++i)
    if (in[i] == rt) m = i;
  dfs(pre, in, post, p, l, m);
  dfs(pre, in, post, p, m + 1, r);
  post.push_back(rt);
}
}  // namespace btree_make_post_pi_impl_

constexpr vecu btree_make_post_pi(vecu const& pre_order, vecu const& in_order) {
  assert(pre_order.size() == in_order.size());
  vecu ret;
  u32 pos = 0;
  btree_make_post_pi_impl_::dfs(pre_order, in_order, ret, pos, 0, (u32)pre_order.size());
  return ret;
}

}  // namespace tifa_libs::graph

#endif