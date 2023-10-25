#define PROBLEM "https://yukicoder.me/problems/no/1775"

#include "../../code/math/nimber.hpp"
#include "../../code/rand/gen.hpp"

tifa_libs::math::nimber64 dp[2][2][128][128], nx[2][2][128][128], w[128][128];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::rand::Gen<std::uniform_int_distribution<u64>> g(1, std::numeric_limits<u64>::max());
  u64 n, m, x, y, z;
  std::cin >> n >> m >> x >> y >> z;
  --x, --y, --z;
  for (u64 i = 0; i < n; ++i)
    for (u64 j = 0; j < i; ++j) w[i][j] = w[j][i] = g();
  for (u64 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    w[u][v] = w[v][u] = 0;
  }
  dp[0][0][x][x] = 1;
  for (u64 L = 1; L <= n; ++L) {
    memset(nx, 0, sizeof(nx));
    for (u32 ky = 0; ky < 2; ++ky)
      for (u32 kz = 0; kz < 2; ++kz)
        for (u64 c = 0; c < n; ++c)
          for (u64 d = 0; d < n; ++d) {
            if (w[c][d] == 0) continue;
            if (ky == 1 && d == y) continue;
            if (kz == 1 && d == z) continue;
            u32 nky = ky | (d == y), nkz = kz | (d == z);
            for (u64 p = 0; p < n; ++p)
              if (p != d) nx[nky][nkz][d][c] += dp[ky][kz][c][p];
          }
    for (u32 ky = 0; ky < 2; ++ky)
      for (u32 kz = 0; kz < 2; ++kz)
        for (u64 i = 0; i < n; ++i)
          for (u64 j = 0; j < n; ++j)
            if (w[i][j] != 0) nx[ky][kz][i][j] *= w[i][j];
    std::swap(dp, nx);
    for (u64 i = 0; i < n; ++i)
      if (dp[1][1][x][i] != 0) {
        std::cout << L << '\n';
        return 0;
      }
  }
  std::cout << "-1\n";
  return 0;
}
