#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/io/fastin.hpp"
#include "../../../include/io/fastout.hpp"
#include "../../../include/io/ios128.hpp"
#include "../base.hpp"

using namespace tifa_libs;

auto [fn_in, fn_ans] = unittest::get_fname_in_ans("others", "io", "io");

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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: single_test<i16>(); break;
    case unittest::TC::example_01: single_test<u16>(); break;
    case unittest::TC::random_00: single_test<i32>(); break;
    case unittest::TC::random_01: single_test<u32>(); break;
    case unittest::TC::random_02: single_test<i64>(); break;
    case unittest::TC::random_03: single_test<u64>(); break;
    case unittest::TC::random_04: single_test<i128>(); break;
    case unittest::TC::random_05: single_test<u128>(); break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}