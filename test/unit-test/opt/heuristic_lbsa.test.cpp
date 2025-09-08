#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/opt/heuristic_lbsa.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using point_t = ptti;

vec<point_t> parse_tsp_data(strnv name) {
  strn filename = std::format("data/others/tsp-vlsi/{}.tsp", name);
#ifndef LOCAL_
  std::fstream fin(filename, std::ios_base::in);
#else
  auto& fin = std::cin;
#endif
  strn s;
  auto drop = [&]() { std::getline(fin, s); };

  u32 n;
  vec<point_t> ret;

  // NAME
  std::getline(fin, s);
  check(s, "NAME : "s + name.data(), check_param(filename));
  // COMMENT
  drop(), drop(), drop();
  // TYPE
  drop();
  // DIMENSION
  fin >> s >> s >> n;
  ret.resize(n);
  drop();
  // EDGE_WEIGHT_TYPE
  drop();
  // NODE_COORD_SECTION
  drop();
  // DATA
  for (u32 i = 1, _; i <= n; ++i) {
    fin >> _ >> ret[i - 1].first >> ret[i - 1].second;
    check(_, i);
  }
  drop();
  // EOF
  std::getline(fin, s);
  check(s, "EOF"s);
  return ret;
}

double fitness(spn<point_t> data, spnu seq) {
  check(data.size(), seq.size());
  double ans = std::hypot(data[seq[0]].first - data[seq.back()].first, data[seq[0]].second - data[seq.back()].second);
  flt_ (u32, i, 1, (u32)seq.size()) ans += std::hypot(data[seq[i]].first - data[seq[i - 1]].first, data[seq[i]].second - data[seq[i - 1]].second);
  return ans;
}

void test(const char* const name, double optimal, u32 L, double p0, u32 K, u32 M, double rerr) {
  auto points = parse_tsp_data(name);
  auto f = [&](spnu seq) { return fitness(points, seq); };
  vecu seq(points.size());
  std::iota(begin(seq), end(seq), 0);
  // std::shuffle(begin(seq), end(seq), std::mt19937(time(nullptr)));
  opt::heuristic_lbsa<vecu, decltype(f)> sa(f, seq, L, p0);
  auto [f_solution, solution] = sa(K, M);

  {
    set<u32> sol_unique;
    for (auto i : solution) sol_unique.insert(i);
    check(sol_unique.size(), solution.size());
  }
  check(f(solution), f_solution);
  check_bool(f_solution >= optimal && (f_solution - optimal) / optimal <= rerr, check_param(name), check_param(optimal), check_param(f_solution), check_param(L), check_param(p0), check_param(K), check_param(M), check_param(rerr));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("bcl380", 1621, 120, .27, 1000, 380, .2); break;
    case unittest::TC::example_01: test("xql662", 2513, 120, .19, 1000, 662, .2); break;
    case unittest::TC::random_00: break;
    case unittest::TC::random_01: break;
    case unittest::TC::random_02: break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}