#define PROBLEM "https://yukicoder.me/problems/no/1775"

#include "../../code/math/nimber.hpp"
#include "../../code/rand/gen.hpp"

tifa_libs::math::nimber64 dp[2][2][128][128], nx[2][2][128][128], w[128][128];

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::rand::Gen<std::uniform_int_distribution<u64>> g(1, std::numeric_limits<u64>::max());
  u64 n, m, x, y, z;
  std::cin >> n >> m >> x >> y >> z;
  --x, --y, --z;
  flt_ (u64, i, 0, n)
    flt_ (u64, j, 0, i) w[i][j] = w[j][i] = g();
  for (u64 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    w[u][v] = w[v][u] = 0;
  }
  dp[0][0][x][x] = 1;
  fle_ (u64, L, 1, n) {
    memset(nx, 0, sizeof(nx));
    flt_ (u32, ky, 0, 2)
      flt_ (u32, kz, 0, 2)
        flt_ (u64, c, 0, n)
          flt_ (u64, d, 0, n) {
            if (w[c][d] == 0) continue;
            if (ky == 1 && d == y) continue;
            if (kz == 1 && d == z) continue;
            u32 nky = ky | (d == y), nkz = kz | (d == z);
            flt_ (u64, p, 0, n)
              if (p != d) nx[nky][nkz][d][c] += dp[ky][kz][c][p];
          }
    flt_ (u32, ky, 0, 2)
      flt_ (u32, kz, 0, 2)
        flt_ (u64, i, 0, n)
          flt_ (u64, j, 0, n)
            if (w[i][j] != 0) nx[ky][kz][i][j] *= w[i][j];
    tifa_libs::swap(dp, nx);
    flt_ (u64, i, 0, n)
      if (dp[1][1][x][i] != 0) {
        std::cout << L << '\n';
        return 0;
      }
  }
  std::cout << "-1\n";
  return 0;
}
