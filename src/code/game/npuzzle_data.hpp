#ifndef TIFALIBS_GAME_NPUZZLE_DATA
#define TIFALIBS_GAME_NPUZZLE_DATA

#include "../util/abs_constexpr.hpp"
#include "../util/util.hpp"

namespace tifa_libs::game {

// clang-format off
enum Dir4 { U, D, L, R };
// clang-format on

// n = k*k-1
class NPuzzleData {
  u32 k, pos0;
  vec<u32> node_;
  vec<Dir4> moves_;
  u32 cost_;

 public:
  constexpr explicit NPuzzleData(u32 k) : k(k) {}

  constexpr auto const &cost() const { return cost_; }
  constexpr auto &node() { return node_; }
  constexpr auto const &node() const { return node_; }
  constexpr auto const &moves() const { return moves_; }

  constexpr bool solved() {
    for (u32 i = 0; i < node_.size(); ++i)
      if (node_[i] != i) return 0;
    return 1;
  }
  constexpr vec<NPuzzleData> next() {
    auto moves = gen_move();
    vec<NPuzzleData> ans(moves.size(), *this);
    for (u32 i = 0; i < moves.size(); ++i) ans[i].move(moves[i]);
    return ans;
  }
  constexpr void move(Dir4 dir) {
    moves_.push_back(dir);
    u32 _ = pos0;
    switch (dir) {
      case U: pos0 -= k; break;
      case D: pos0 += k; break;
      case L: --pos0; break;
      case R: ++pos0; break;
    }
    std::swap(node_[_], node_[pos0]);
    cost_ = gen_cost();
  }

  constexpr auto operator<=>(NPuzzleData const &node) const { return node_ <=> node.node_; }

  friend std::istream &operator>>(std::istream &is, NPuzzleData &np) {
    np.node_.resize(np.k * np.k);
    for (auto &i : np.node_) is >> i;
    np.pos0 = u32(std::find(np.node_.begin(), np.node_.end(), 0) - np.node_.begin());
    np.cost_ = np.gen_cost();
    return is;
  }

 private:
  constexpr vec<Dir4> gen_move() const {
    vec<Dir4> ans;
    if (pos0 / k) ans.push_back(U);
    if (pos0 / k != k - 1) ans.push_back(D);
    if (pos0 % k) ans.push_back(L);
    if (pos0 % k != k - 1) ans.push_back(R);
    return ans;
  }
  constexpr u32 gen_cost() const {
    u32 h1 = 0, h2 = 0;
    for (u32 i = 0; i < k; ++i)
      for (u32 j = 0; j < k; ++j)
        if (u32 _ = node_[k * i + j]; _ != k * i + j && _) ++h1, h2 += u32(abs((i32)i - i32(_ / k)) + abs((i32)j - i32(_ % k)));
    return std::max(h1, h2) + (u32)moves_.size();
  }
};

}  // namespace tifa_libs::game

#endif