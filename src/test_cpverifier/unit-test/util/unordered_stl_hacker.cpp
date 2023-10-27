#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/util/unordered_stl_hacker.hpp"

#include "../base.hpp"

template <class T>
void test_unordered_stl_hacker(usz n) {
  auto list = tifa_libs::util::unordered_stl_hacker<T>(n);
  std::unordered_set<T> s;
  for (auto i : list) s.insert(i);
  check_bool(s.bucket_size(0) == n, check_param(s.bucket_size(0)), check_param(list));
}

int main() {
  tifa_libs::unittest::pre_test();

  test_unordered_stl_hacker<std::string>(1000);
  test_unordered_stl_hacker<i32>(1000);
  test_unordered_stl_hacker<u32>(1000);
  test_unordered_stl_hacker<i64>(1000);
  test_unordered_stl_hacker<u64>(1000);

  tifa_libs::unittest::post_test();
}