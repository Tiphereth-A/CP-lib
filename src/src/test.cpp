// #pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <cpuid.h>
using namespace std;

void cpu_name() {
  static char s[0x40];
  static unsigned x[4] = {0, 0, 0, 0};
  constexpr unsigned N = 0x80000000;
  __cpuid(N, x[0], x[1], x[2], x[3]);
  for (unsigned i = N, ed = x[0]; i <= ed; ++i) {
    __cpuid(i, x[0], x[1], x[2], x[3]);
    if (i == N + 2) memcpy(s, x, sizeof(x));
    if (i == N + 3) memcpy(s + 16, x, sizeof(x));
    if (i == N + 4) memcpy(s + 32, x, sizeof(x));
  }
  cout << s << endl;
}

int main() {
  cpu_name();
  auto st = chrono::high_resolution_clock::now();

  volatile unsigned n = 3000;
  bitset<30> ans;
  for (volatile unsigned i = 1; i <= n; ++i)
    for (volatile unsigned j = 1; j <= n; j += 2)
      for (volatile unsigned k = 1; k <= n; k += 4) ans |= i | j | k;

  auto ed = chrono::high_resolution_clock::now();
  cout << fixed << setprecision(6) << chrono::duration_cast<chrono::nanoseconds>(ed - st).count() * 1e-6l << " ms" << endl;
  long double nn = 1.l * n * (n >> 1) * (n >> 2) / chrono::duration_cast<chrono::nanoseconds>(ed - st).count() * 1e9;
  // assert(nn > 3e9);
  cout << scientific << nn << endl;
}