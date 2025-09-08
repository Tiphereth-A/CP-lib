#ifndef TIFALIBS_GAME_NPUZZLE_DATA
#define TIFALIBS_GAME_NPUZZLE_DATA

#include "../util/traits_others.hpp"

namespace tifa_libs::game {

// n = k*k-1
class npuzzle_data {
  static inline vecu fin_node, fin_pos;
  static inline vvecu costs;

  u32 k, p0, cost_;

 public:
  static inline u32 limit = UINT32_MAX;
  static CEXP void set_fin(u32 k, vecu CR fin) NE {
    assert(fin.size() == k * k), fin_node = fin, fin_pos.resize(k * k);
    flt_ (u32, i, 0, k * k) fin_pos[fin_node[i]] = i;
    costs.resize(k * k, vecu(k * k));
    flt_ (u32, p, 1, k * k)
      flt_ (u32, q, 0, k * k) costs[p][q] = u32(abs(i32(p / k) - i32(q / k)) + abs(i32(p % k) - i32(q % k))) / 2 + (p != q);
  }

  vecu node;
  strn moves;

  CEXPE npuzzle_data(u32 k) noexcept : k(k), p0(0), cost_(0), node(k * k), moves() { assert(k < 65535); }

  CEXP auto CR cost() CNE { return cost_; }
  CEXP bool solved() CNE { return node == fin_node; }
  CEXP vec<npuzzle_data> next() CNE {
    const char lst = moves.empty() ? ' ' : moves.back();
    strn nxts;
    if (p0 / k && lst != 'D') nxts += 'U';
    if (p0 / k != k - 1 && lst != 'U') nxts += 'D';
    if (p0 % k && lst != 'R') nxts += 'L';
    if (p0 % k != k - 1 && lst != 'L') nxts += 'R';
    vec<npuzzle_data> ans;
    for (char d : nxts) {
      auto nxt = *this;
      if (nxt.move(d); nxt.cost_ <= limit) ans.push_back(nxt);
    }
    return ans;
  }
  CEXP void move(char dir) NE {
    moves.push_back(dir), ++cost_;
    const u32 pre = p0;
    switch (dir) {
      case 'U': p0 -= k; break;
      case 'D': p0 += k; break;
      case 'L': --p0; break;
      case 'R': ++p0; break;
    }
    cost_ -= costs[pre][fin_pos[node[pre]]] + costs[p0][fin_pos[node[p0]]];
    cost_ += costs[pre][fin_pos[node[p0]]] + costs[p0][fin_pos[node[pre]]];
    swap(node[pre], node[p0]);
  }
  CEXP auto operator<=>(npuzzle_data CR r) CNE { return node <=> r.node; }
  CEXP bool operator==(npuzzle_data CR r) CNE { return std::is_eq(*this <=> r); }
  friend auto &operator>>(istream_c auto &is, npuzzle_data &np) NE {
    for (auto &i : np.node) is >> i;
    np.p0 = u32(find(np.node, 0) - begin(np.node));
    flt_ (u32, p, 0, (u32)np.node.size())
      if (np.node[p]) np.cost_ += costs[p][fin_pos[np.node[p]]];
    return is;
  }
};

}  // namespace tifa_libs::game

#endif