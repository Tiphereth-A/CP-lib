#ifndef TIFALIBS_GAME_NPUZZLE_DATA
#define TIFALIBS_GAME_NPUZZLE_DATA

#include "../util/abs_constexpr.hpp"
#include "../util/util.hpp"

namespace tifa_libs::game {

// n = k*k-1
class NPuzzleData {
  static inline vec<u32> fin_node, fin_pos;
  static inline vvec<u32> pos_cost;

  u32 k, pos0;
  u32 cost_;

 public:
  static inline u32 limit = UINT32_MAX;
  static constexpr void set_fin(u32 k, vec<u32> const &fin) {
    assert(fin.size() == k * k);
    fin_node = fin;
    fin_pos.resize(k * k);
    for (u32 i = 0; i < k * k; ++i) fin_pos[fin_node[i]] = i;
    pos_cost.resize(k * k, vec<u32>(k * k));
    for (u32 p = 1; p < k * k; ++p)
      for (u32 q = 0; q < k * k; ++q) pos_cost[p][q] = u32(abs(i32(p / k) - i32(q / k)) + abs(i32(p % k) - i32(q % k)));
  }

  vec<u32> node;
  strn moves;

  constexpr explicit NPuzzleData(u32 k) : k(k), pos0(0), cost_(0), node(k * k), moves() {}

  constexpr auto const &cost() const { return cost_; }
  constexpr bool solved() { return node == fin_node; }
  constexpr vec<NPuzzleData> next() {
    strn moves;
    {
      char lst = moves.back();
      if (pos0 / k && lst != 'D') moves += 'U';
      if (pos0 / k != k - 1 && lst != 'U') moves += 'D';
      if (pos0 % k && lst != 'R') moves += 'L';
      if (pos0 % k != k - 1 && lst != 'L') moves += 'R';
    }
    vec<NPuzzleData> ans;
    for (char d : moves) {
      auto nxt = *this;
      nxt.move(d);
      if (nxt.cost_ <= limit) ans.push_back(nxt);
    }
    return ans;
  }
  constexpr void move(char dir) {
    moves.push_back(dir);
    ++cost_;
    u32 _ = pos0;
    switch (dir) {
      case 'U': pos0 -= k; break;
      case 'D': pos0 += k; break;
      case 'L': --pos0; break;
      case 'R': ++pos0; break;
    }
    cost_ += pos_cost[_][fin_pos[node[pos0]]];
    cost_ -= pos_cost[pos0][fin_pos[node[pos0]]];
    std::swap(node[_], node[pos0]);
  }
  constexpr auto operator<=>(NPuzzleData const &r) const { return node <=> r.node; }
  friend std::istream &operator>>(std::istream &is, NPuzzleData &np) {
    for (auto &i : np.node) is >> i;
    np.pos0 = u32(std::find(np.node.begin(), np.node.end(), 0) - np.node.begin());
    for (u32 p = 0; p < np.node.size(); ++p)
      if (np.node[p]) np.cost_ += pos_cost[p][fin_pos[np.node[p]]];
    return is;
  }
};

}  // namespace tifa_libs::game

#endif