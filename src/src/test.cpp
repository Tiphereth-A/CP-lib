// #pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
#include <cpuid.h>
using namespace std;

void cpuid() {
  static char brand[0x40];
  static unsigned info[4] = {0, 0, 0, 0};
  constexpr unsigned N = 0x80000000;
  __cpuid(N, info[0], info[1], info[2], info[3]);
  unsigned nexids = info[0];
  for (unsigned i = N; i <= nexids; ++i) {
    __cpuid(i, info[0], info[1], info[2], info[3]);
    if (i == N + 2) memcpy(brand, info, sizeof(info));
    if (i == N + 3) memcpy(brand + 16, info, sizeof(info));
    if (i == N + 4) memcpy(brand + 32, info, sizeof(info));
  }
  cout << brand << endl;
}

int main() {
  cpuid();
  auto st = chrono::high_resolution_clock::now();

  volatile int n = 3000;
  bitset<30> ans;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; j += 2)
      for (int k = 1; k <= n; k += 4) ans |= i | j | k;

  auto ed = chrono::high_resolution_clock::now();
  cout << fixed << setprecision(12) << chrono::duration_cast<chrono::nanoseconds>(ed - st).count() * 1e-6l << " ms" << endl;
  long double nn = 1.l * n * (n >> 1) * (n >> 2);
  cout << nn / chrono::duration_cast<chrono::seconds>(ed - st).count() << endl;
}