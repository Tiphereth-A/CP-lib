#ifndef TIFALIBS_GAME_NPUZZLE_DATA
#define TIFALIBS_GAME_NPUZZLE_DATA

#include "../util/util.hpp"

namespace tifa_libs::game {

// n = k*k-1
class NPuzzleData {
  static inline vecu fin_node, fin_pos;
  static inline vvecu pos_cost;

  u32 k, pos0, cost_;

 public:
  static inline u32 limit = UINT32_MAX;
  static CEXP void set_fin(u32 k, vecu CR fin) {
    assert(fin.size() == k * k), fin_node = fin, fin_pos.resize(k * k);
    flt_ (u32, i, 0, k * k) fin_pos[fin_node[i]] = i;
    pos_cost.resize(k * k, vecu(k * k));
    flt_ (u32, p, 1, k * k)
      flt_ (u32, q, 0, k * k) pos_cost[p][q] = u32(abs(i32(p / k) - i32(q / k)) + abs(i32(p % k) - i32(q % k)));
  }

  vecu node;
  strn moves;

  CEXPE NPuzzleData(u32 k) : k(k), pos0(0), cost_(0), node(k * k), moves() { assert(k < 65535); }

  CEXP auto CR cost() const { return cost_; }
  CEXP bool solved() { return node == fin_node; }
  CEXP vec<NPuzzleData> next() {
    strn moves;
    {
      const char lst = moves.back();
      if (pos0 / k && lst != 'D') moves += 'U';
      if (pos0 / k != k - 1 && lst != 'U') moves += 'D';
      if (pos0 % k && lst != 'R') moves += 'L';
      if (pos0 % k != k - 1 && lst != 'L') moves += 'R';
    }
    vec<NPuzzleData> ans;
    for (char d : moves) {
      auto nxt = *this;
      if (nxt.move(d); nxt.cost_ <= limit) ans.push_back(nxt);
    }
    return ans;
  }
  CEXP void move(char dir) {
    moves.push_back(dir), ++cost_;
    const u32 _ = pos0;
    switch (dir) {
      case 'U': pos0 -= k; break;
      case 'D': pos0 += k; break;
      case 'L': --pos0; break;
      case 'R': ++pos0; break;
    }
    cost_ += pos_cost[_][fin_pos[node[pos0]]] - pos_cost[pos0][fin_pos[node[pos0]]], swap(node[_], node[pos0]);
  }
  CEXP auto operator<=>(NPuzzleData CR r) const { return node <=> r.node; }
  friend std::istream &operator>>(std::istream &is, NPuzzleData &np) {
    for (auto &i : np.node) is >> i;
    np.pos0 = u32(std::ranges::find(np.node, 0) - np.node.begin());
    flt_ (u32, p, 0, (u32)np.node.size())
      if (np.node[p]) np.cost_ += pos_cost[p][fin_pos[np.node[p]]];
    return is;
  }
};

}  // namespace tifa_libs::game

#endif