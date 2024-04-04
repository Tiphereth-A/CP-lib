#ifndef TIFALIBS_GAME_SUDOKU
#define TIFALIBS_GAME_SUDOKU

#include "../math/isqrt.hpp"
#include "../util/dlx.hpp"

namespace tifa_libs::game {

constexpr v3ecu sudoku_solver(vvecu const &data, bool get_all_solution = false) {
  const u32 n = math::isqrt(data.size()), n2 = (u32)data.size(), n4 = n2 * n2;
  assert(n <= 65536 && n * n == n2);
  vvecb g(n2 * n4, vecb(4 * n4));
  bool not_filled = true;
  for (u32 i = 0; i < n2; ++i)
    for (u32 j = 0; j < n2; ++j)
      for (u32 k = 1; k <= n2; ++k) {
        if (data[i][j] && data[i][j] != k) continue;
        not_filled |= data[i][j] == 0;
        auto _ = (k - 1) * n4 + i * n2 + j;
        g[_][i * n2 + j] = g[_][i * n2 + k + n4 - 1] = g[_][j * n2 + k + n4 * 2 - 1] = g[_][(i / n * n + j / n) * n2 + k + n4 * 3 - 1] = true;
      }
  if (!not_filled) return {data};
  v3ecu ans;
  util::DLX(g, get_all_solution).dance([&](vec<usz> const &res) -> void {
    vvecu dt = data;
    for (usz _ : res) dt[(_ - 1) % n4 / n2][(_ - 1) % n2] = u32((_ - 1) / n4 + 1);
    ans.push_back(dt);
  });
  return ans;
}

}  // namespace tifa_libs::game

#endif