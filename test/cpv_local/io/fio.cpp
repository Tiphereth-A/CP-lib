// competitive-verifier: STANDALONE

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/io/i128/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

strn fn_in = "test/cpv_local/_data/others/io/io.in";
strn fn_ans = "test/cpv_local/_data/others/io/io.out";

template <class T>
void single_test() {
  CEXP T MIN = [] {
    if CEXP (imost64_c<T>) return std::numeric_limits<T>::min();
    else if (sint_c<T>) return (T)1 << (sizeof(T) * 8 - 1);
    else return (T)0;
  }(),
         MAX = (T)~MIN;

  T x;
  FILE* f;

  f = fopen(fn_in.c_str(), "w");
  fout.rebind(f);
  fout << MIN;
  fout.flush();
  fout.rebind(stdout);
  fclose(f);
  f = fopen(fn_in.c_str(), "r");
  fid_stdin.rebind(f);
  fin >> x;
  fid_stdin.rebind(stdin);
  fclose(f);
  check(x, MIN);

  f = fopen(fn_in.c_str(), "w");
  fout.rebind(f);
  fout << MAX;
  fout.flush();
  fout.rebind(stdout);
  fclose(f);
  f = fopen(fn_in.c_str(), "r");
  fid_stdin.rebind(f);
  fin >> x;
  fid_stdin.rebind(stdin);
  fclose(f);
  check(x, MAX);
}

int main() {
  timer_(single_test<i16>());
  timer_(single_test<u16>());
  timer_(single_test<i32>());
  timer_(single_test<u32>());
  timer_(single_test<i64>());
  timer_(single_test<u64>());
  timer_(single_test<i128>());
  timer_(single_test<u128>());
}