// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2823

#include "../../../src/geo2d/min_cover_c/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Circle2 = geo::circle<data_t>;

int main() {
  cout << std::fixed << std::setprecision(2);

  u32 n;
  cin >> n;
  vec<Point2> vp(n);
  for (auto& i : vp) cin >> i;
  std::ranges::shuffle(vp, std::mt19937{std::default_random_engine{}()});
  auto ans = geo::min_cover_C(vp);
  cout << ans << '\n';
}