#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/util/unordered_stl_hacker.hpp"

#include "../base.hpp"


template <class T>
void test_unordered_stl_hacker(usz n) {
  auto list = tifa_libs::util::unordered_stl_hacker<T>(n);
  std::unordered_set<T> s;
  for (auto i : list) s.insert(i);
  check_bool(s.bucket_size(0) == n, check_param(s.bucket_size(0)), check_param(list));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test_unordered_stl_hacker<strn>(1000); break;
    case tifa_libs::unittest::ts_example_01: test_unordered_stl_hacker<i32>(1000); break;
    case tifa_libs::unittest::ts_random_00: test_unordered_stl_hacker<u32>(1000); break;
    case tifa_libs::unittest::ts_random_01: test_unordered_stl_hacker<i64>(1000); break;
    case tifa_libs::unittest::ts_random_02: test_unordered_stl_hacker<u64>(1000); break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}