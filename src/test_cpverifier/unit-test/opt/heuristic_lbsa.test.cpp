#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/opt/heuristic_lbsa.hpp"

#include "../base.hpp"

using point_t = ptt<i32>;

vec<point_t> parse_tsp_data(std::string const& name) {
  std::string filename = "src/data/tsp-vlsi/" + name + ".tsp";
#ifndef LOCAL_
  std::fstream fin(filename, std::ios_base::in);
#else
  auto& fin = std::cin;
#endif
  std::string s;
  auto drop = [&]() { std::getline(fin, s); };

  u32 n;
  vec<point_t> ret;

  // NAME
  std::getline(fin, s);
  check(s, "NAME : " + name, check_param(filename));
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
  check(s, std::string("EOF"));
  return ret;
}

double fitness(vec<point_t> const& data, vec<u32> const& seq) {
  check(data.size(), seq.size());
  double ans = std::hypot(data[seq[0]].first - data[seq.back()].first, data[seq[0]].second - data[seq.back()].second);
  for (u32 i = 1; i < seq.size(); ++i) ans += std::hypot(data[seq[i]].first - data[seq[i - 1]].first, data[seq[i]].second - data[seq[i - 1]].second);
  return ans;
}

void test(const char* const name, double optimal, u32 L, double p0, u32 K, u32 M, double rerr) {
  auto points = parse_tsp_data(name);
  auto f = [&](vec<u32> const& seq) { return fitness(points, seq); };
  vec<u32> seq(points.size());
  std::iota(seq.begin(), seq.end(), 0);
  // std::shuffle(seq.begin(), seq.end(), std::mt19937(time(nullptr)));
  tifa_libs::opt::heuristic_lbsa<vec<u32>, decltype(f)> sa(f, seq, L, p0);
  auto [f_solution, solution] = sa(K, M);

  {
    std::set<u32> sol_unique;
    for (auto i : solution) sol_unique.insert(i);
    check(sol_unique.size(), solution.size());
  }
  check(f(solution), f_solution);
  check_bool(f_solution >= optimal && (f_solution - optimal) / optimal <= rerr, check_param(name), check_param(optimal), check_param(f_solution), check_param(L), check_param(p0), check_param(K), check_param(M), check_param(rerr));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00:
      test("bcl380", 1621, 120, .27, 1000, 380, .2);
      break;
    case tifa_libs::unittest::ts_example_01:
      test("xql662", 2513, 120, .19, 1000, 662, .2);
      break;
    default:
      break;
  }

  tifa_libs::unittest::post_test();
}