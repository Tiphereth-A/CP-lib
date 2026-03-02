// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/12304

#include "../../../src/geo2d/make_c/rcc_ex/lib.hpp"
#include "../../../src/geo2d/make_c/rll/lib.hpp"
#include "../../../src/geo2d/make_c/rpl/lib.hpp"
#include "../../../src/geo2d/tan/cp/lib.hpp"
#include "../../../src/geo2d/tcenter/i/lib.hpp"
#include "../../../src/geo2d/tcenter/o/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using Triangle = geo::triangle<data_t>;
using Circle2 = geo::circle<data_t>;

CEXP data_t PI = pi_v<data_t>;

int main() {
  cout << std::fixed << std::setprecision(6);

  strn s;
  while (cin >> s) {
    if (s == "CircumscribedCircle") {
      Triangle t;
      cin >> t;
      Point2 o = center_O(t);
      data_t r = radius_O(t);
      cout << '(' << o.x << ',' << o.y << ',' << r << ")\n";
    } else if (s == "InscribedCircle") {
      Triangle t;
      cin >> t;
      Point2 i = center_I(t);
      data_t r = radius_I(t);
      cout << '(' << i.x << ',' << i.y << ',' << r << ")\n";
    } else if (s == "TangentLineThroughPoint") {
      Circle2 c;
      Point2 p;
      cin >> c >> p;
      auto tps = tan_CP(c, p);
      if (!tps) {
        cout << "[]\n";
      } else {
        auto [tps0, tps1] = tps.value();
        Point2 d1 = Line2{p, tps0}.direction(), d2 = Line2{p, tps1}.direction();
        data_t angle1 = atan2(d1.y, d1.x) / PI * 180;
        data_t angle2 = atan2(d2.y, d2.x) / PI * 180;
        if (angle1 < 0) angle1 += 180;
        if (angle1 >= 180) angle1 -= 180;
        if (angle2 < 0) angle2 += 180;
        if (angle2 >= 180) angle2 -= 180;
        if (is_eq(angle1, angle2)) {
          cout << '[' << angle1 << "]\n";
        } else {
          if (angle1 > angle2) std::swap(angle1, angle2);
          cout << '[' << angle1 << ',' << angle2 << "]\n";
        }
      }
    } else if (s == "CircleThroughAPointAndTangentToALineWithRadius") {
      Point2 p;
      Line2 l;
      data_t r;
      cin >> p >> l >> r;
      auto cs = make_C_rPL(r, p, l);
      if (!cs) {
        cout << "[]\n";
      } else {
        auto [cs0, cs1] = cs.value();
        if (cs1.o < cs0.o) std::swap(cs0, cs1);
        if (cs0.o == cs1.o) {
          cout << "[(" << cs0.o.x << ',' << cs0.o.y << ")]\n";
        } else {
          cout << "[(" << cs0.o.x << ',' << cs0.o.y << "),(" << cs1.o.x << ',' << cs1.o.y << ")]\n";
        }
      }
    } else if (s == "CircleTangentToTwoLinesWithRadius") {
      Line2 l1, l2;
      data_t r;
      cin >> l1 >> l2 >> r;
      auto cs_ = make_C_rLL(r, l1, l2);
      if (!cs_) {
        cout << "[]\n";
      } else {
        auto [cs0, cs1, cs2, cs3] = cs_.value();
        vec<Circle2> cs{cs0, cs1, cs2, cs3};
        std::ranges::sort(cs, [](Circle2 CR lhs, Circle2 CR rhs) { return lhs.o < rhs.o; });
        cout << "[(" << cs[0].o.x << ',' << cs[0].o.y << "),(" << cs[1].o.x << ',' << cs[1].o.y << "),(" << cs[2].o.x << ',' << cs[2].o.y << "),(" << cs[3].o.x << ',' << cs[3].o.y << ")]\n";
      }
    } else if (s == "CircleTangentToTwoDisjointCirclesWithRadius") {
      Circle2 c1, c2;
      data_t r;
      cin >> c1 >> c2 >> r;
      auto cs = make_C_rCC_ex(r, c1, c2);
      if (!cs) {
        cout << "[]\n";
      } else {
        auto [cs0, cs1] = cs.value();
        if (cs1.o < cs0.o) std::swap(cs0, cs1);
        if (cs0.o == cs1.o) {
          cout << "[(" << cs0.o.x << ',' << cs0.o.y << ")]\n";
        } else {
          cout << "[(" << cs0.o.x << ',' << cs0.o.y << "),(" << cs1.o.x << ',' << cs1.o.y << ")]\n";
        }
      }
    }
  }
}