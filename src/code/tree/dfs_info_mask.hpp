#ifndef TIFALIBS_TREE_DFS_INFO_MASK
#define TIFALIBS_TREE_DFS_INFO_MASK

namespace tifa_libs::graph {

enum tree_dfs_info_mask {
  td_dfn = 1,
  td_sz = 2,
  td_fa = 4,
  td_dep = 8,
  td_maxson = 16,
  td_maxdfn = 32,
  td_euler = 64,
  td_go = 128,
  tdw_dis = 256
};

}  // namespace tifa_libs::graph

#endif