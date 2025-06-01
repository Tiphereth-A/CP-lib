#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../include/ds/fhq_treap.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 q;
  std::cin >> q;
  ds::fhq_treap<pttuu> tr;
  for (u64 i = 0, op, k, v; i < q; ++i) {
    std::cin >> op >> k;
    auto it = tr.prev({k, UINT64_MAX});
    if (op) {
      std::cout << (it && it->first == k ? it->second : 0) << '\n';
    } else {
      std::cin >> v;
      if (it && it->first == k) tr.erase(it.value()), tr.insert({k, v});
      else tr.insert({k, v});
    }
  }
  return 0;
}
