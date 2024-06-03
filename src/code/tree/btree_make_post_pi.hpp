#ifndef TIFALIBS_TREE_BTREE_MAKE_POST_PI
#define TIFALIBS_TREE_BTREE_MAKE_POST_PI

#include "../util/util.hpp"

namespace tifa_libs::graph {

namespace btree_make_post_pi_impl_ {
CEXP void dfs(spnu pre, spnu in, vecu& post, u32& p, u32 l, u32 r) {
  if (l >= r) return;
  u32 rt = pre[p++], m = -1_u32;
  flt_ (u32, i, l, r)
    if (in[i] == rt) m = i;
  dfs(pre, in, post, p, l, m), dfs(pre, in, post, p, m + 1, r), post.push_back(rt);
}
}  // namespace btree_make_post_pi_impl_

CEXP vecu btree_make_post_pi(spnu pre_order, spnu in_order) {
  assert(pre_order.size() == in_order.size());
  vecu ret;
  u32 pos = 0;
  return btree_make_post_pi_impl_::dfs(pre_order, in_order, ret, pos, 0, (u32)pre_order.size()), ret;
}

}  // namespace tifa_libs::graph

#endif