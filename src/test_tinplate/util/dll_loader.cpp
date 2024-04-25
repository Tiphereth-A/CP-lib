// From <https://judge.yosupo.jp/submission/199073>
#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_hex_big_integers"

#include "../../code/util/dll_loader.hpp"

CEXP const char *LIB_PATH = "/usr/lib/x86_64-linux-gnu/libgmp.so.10";

using mpz_t = char[16];
tifa_libs::util::DLL *gmp;
int t;
char sa[2000010], sb[2000010], sq[2000010];

int main(int, char **argv) {
  if (getenv("LD_PRELOAD") == nullptr) {
    setenv("LD_PRELOAD", LIB_PATH, 1);
    execve("/proc/self/exe", argv, environ);
    exit(0);
  }
  gmp = new tifa_libs::util::DLL(LIB_PATH);

  mpz_t a, b, q, r;

  gmp->call("__gmpz_init", a);
  gmp->call("__gmpz_init", b);
  gmp->call("__gmpz_init", q);
  gmp->call("__gmpz_init", r);

  [[maybe_unused]] auto _ = scanf("%d", &t);
  while (t--) {
    [[maybe_unused]] auto _ = scanf("%s%s", sa, sb);
    gmp->call("__gmpz_set_str", a, sa, 16);
    gmp->call("__gmpz_set_str", b, sb, 16);
    gmp->call("__gmpz_mul", q, a, b);
    gmp->call("__gmpz_get_str", sq, -16, q);
    puts(sq);
  }

  gmp->call("__gmpz_clear", a);
  gmp->call("__gmpz_clear", b);
  gmp->call("__gmpz_clear", q);
  gmp->call("__gmpz_clear", r);
  return 0;
}

/*
This problem has $T$ cases.
Given hexadecimal integers $A$ and $B$, print hexadecimal integer $AB$.

$1 \leq T \leq 160000$
$0 \leq |A|, |B| < 16^{16\times 10^5}$
The sum of (the number of characters in $A$) $+$ (the number of characters in $B$) over all test cases does not exceed $3200002$.

**input**

$T$
$A$ $B$
$\vdots$
$A$ $B$

**output**

$AB$
$\vdots$
$AB$
*/

/*
9
47 FF
50 FF
3 -FF
0 -FF
-A0 -EFE
1234567890ABCDEF1234567890ABCDEF FEDCBA9876543210FEDCBA9876543210
-1234567890ABCDEF1234567890ABCDEF FEDCBA9876543210FEDCBA9876543210
-1234567890ABCDEF1234567890ABCDEF -FEDCBA9876543210FEDCBA9876543210
1234567890ABCDEF1234567890ABCDEF -1234567890ABCDEF1234567890ABCDEF
===================================================================================
46B9
4FB0
-2FD
0
95EC0
121FA00ACD77D74247ACC913F0513B7458FAB207783AF122236D88FE55618CF0
-121FA00ACD77D74247ACC913F0513B7458FAB207783AF122236D88FE55618CF0
121FA00ACD77D74247ACC913F0513B7458FAB207783AF122236D88FE55618CF0
-14B66DC328828BCA8DE2CC20802F69A4DDA24EF786D72FEA6475F09A2F2A521
*/