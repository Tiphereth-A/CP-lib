#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/rand/heuristic_lbsa.hpp"

#include "../base.hpp"

vec<ptt<u32>> parse_tsp_data(char const* const filename) {
  std::fstream fin(filename, std::ios_base::in);
  std::string s;
  auto drop = [&]() { std::getline(fin, s); };

  u32 n;
  vec<ptt<u32>> ret;

  // NAME
  drop();
  // COMMENT
  drop(), drop(), drop();
  // TYPE
  drop();
  // DIMENSION
  fin >> s >> s >> n;
  ret.resize(n);
  // EDGE_WEIGHT_TYPE
  drop();
  // NODE_COORD_SECTION
  drop();
  for (u32 i = 1; i <= n; ++i) fin >> i >> ret[i - 1].first >> ret[i - 1].second;
  return ret;
}

double fitness(vec<ptt<u32>> const& data, vec<u32> const& seq) {
  double ans = std::hypot(data[seq[0]].first - data[seq.back()].first, data[seq[0]].second - data[seq.back()].second);
  for (u32 i = 1; i < seq.size(); ++i) ans += std::hypot(data[seq[i]].first - data[seq[i - 1]].first, data[seq[i]].second - data[seq[i - 1]].second);
  return ans;
}

void test(std::string const& name, double optimal, u32 L, double p0, u32 K, u32 M, double rerr) {
  auto points = parse_tsp_data(("src/data/tsp-vlsi/" + name + ".tsp").data());
  auto f = [&](vec<u32> const& seq) { return fitness(points, seq); };
  vec<u32> seq(points.size());
  std::iota(seq.begin(), seq.end(), 0);
  tifa_libs::rand::heuristic_lbsa<vec<u32>, decltype(f)> sa(f, seq, L, p0);
  auto [f_solution, solution] = sa(K, M);

  check_bool(std::abs(f_solution - optimal) / optimal <= rerr, check_param(optimal), check_param(L), check_param(p0), check_param(K), check_param(M), check_param(rerr), check_param(f_solution));
}

int main() {
  tifa_libs::unittest::pre_test();

  test("bcl380", 1621, 120, .27, 1000, 380, .03);
  test("xql662", 2513, 120, .19, 1000, 662, .03);
  test("xit1083", 3558, 120, .16, 1000, 1083, .03);
  test("xsc6880", 21537, 120, .15, 1000, 6880, .03);

  tifa_libs::unittest::post_test();
}