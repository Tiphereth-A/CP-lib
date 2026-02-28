// competitive-verifier: STANDALONE

#include "../../../src/rand/gen/lib.hpp"
#include "../../../src/util/unordered_stl_hacker/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

template <class T>
void test_unordered_stl_hacker(usz n) {
  timer_(auto list = unordered_stl_hacker<T>(n));
  std::unordered_set<T> s;
  for (auto i : list) s.insert(i);
  check_bool(s.bucket_size(0) == n, check_param(s.bucket_size(0)), check_param(list));
}

int main() {
  timer_(test_unordered_stl_hacker<strn>(1000));
  timer_(test_unordered_stl_hacker<i32>(1000));
  timer_(test_unordered_stl_hacker<u32>(1000));
  timer_(test_unordered_stl_hacker<i64>(1000));
  timer_(test_unordered_stl_hacker<u64>(1000));
}