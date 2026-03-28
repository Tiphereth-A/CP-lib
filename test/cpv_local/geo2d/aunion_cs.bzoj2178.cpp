// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2178

#include "../../../src/edh/discretization/lib.hpp"
#include "../../../src/geo2d/aunion/cs/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Circle2 = circle<data_t>;

int main() {
  cout << std::fixed << std::setprecision(3);

  u32 n;
  cin >> n;
  vec<Circle2> cs(n);
  cin >> cs;
  auto res = aunion_Cs(uniq(cs));
  cout << res[0] << '\n';
}