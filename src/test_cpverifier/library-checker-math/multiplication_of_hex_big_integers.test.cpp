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
