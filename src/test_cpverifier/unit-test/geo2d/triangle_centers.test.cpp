#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/ang_pp.hpp"
#include "../../../code/geo2d/area_triedges.hpp"
#include "../../../code/geo2d/dist_pl.hpp"
#include "../../../code/geo2d/point_is_in_middle.hpp"
#include "../../../code/geo2d/tcenter_e.hpp"
#include "../../../code/geo2d/tcenter_g.hpp"
#include "../../../code/geo2d/tcenter_h.hpp"
#include "../../../code/geo2d/tcenter_i.hpp"
#include "../../../code/geo2d/tcenter_n.hpp"
#include "../../../code/geo2d/tcenter_o.hpp"
#include "../../../code/geo2d/tcenter_x.hpp"
#include "../base.hpp"

using tifa_libs::is_zero, tifa_libs::is_eq;
using tifa_libs::geo::point, tifa_libs::geo::line, tifa_libs::geo::triangle;

template <class T>
void test_e(triangle<T> CR t) {
  point<T> ea = tifa_libs::geo::center_EA(t), eb = tifa_libs::geo::center_EB(t), ec = tifa_libs::geo::center_EC(t);
  point<T> i = tifa_libs::geo::center_I(t);
  point<T> he = tifa_libs::geo::center_H(triangle<T>(ea, eb, ec));

  check(he, i, check_param(t), check_param(ea), check_param(eb), check_param(ec));
}

template <class T>
void test_g(triangle<T> CR t) {
  point<T> g = tifa_libs::geo::center_G(t);
  point<T> mab = mid_point(t.A, t.B), mbc = mid_point(t.B, t.C), mca = mid_point(t.C, t.A);

  check_bool(tifa_libs::geo::is_in_middle(t.A, g, mbc), check_param(t), check_param(g), check_param(mbc));
  check_bool(tifa_libs::geo::is_in_middle(t.B, g, mca), check_param(t), check_param(g), check_param(mca));
  check_bool(tifa_libs::geo::is_in_middle(t.C, g, mab), check_param(t), check_param(g), check_param(mab));
}

template <class T>
void test_h(triangle<T> CR t) {
  point<T> h = tifa_libs::geo::center_H(t);
  point<T> uva = (t.A - h).do_unit(), uvb = (t.B - h).do_unit(), uvc = (t.C - h).do_unit();
  point<T> uab = (t.A - t.B).do_unit(), ubc = (t.B - t.C).do_unit(), uca = (t.C - t.A).do_unit();

  check_bool(is_zero(uva * ubc), check_param(t), check_param(h), check_param(uva), check_param(ubc));
  check_bool(is_zero(uvb * uca), check_param(t), check_param(h), check_param(uva), check_param(uca));
  check_bool(is_zero(uvc * uab), check_param(t), check_param(h), check_param(uva), check_param(uab));

  line<T> lab(t.A, t.B), lbc(t.B, t.C), lca(t.C, t.A);
  T dist_ah = tifa_libs::geo::dist_PP(t.A, h), dist_bh = tifa_libs::geo::dist_PP(t.B, h), dist_ch = tifa_libs::geo::dist_PP(t.C, h);
  T dist_hd = tifa_libs::geo::dist_PL(h, lbc), dist_he = tifa_libs::geo::dist_PL(h, lca), dist_hf = tifa_libs::geo::dist_PL(h, lab);

  check_bool(is_eq(dist_ah * dist_hd, dist_bh * dist_he) && is_eq(dist_bh * dist_he, dist_ch * dist_hf), check_param(t), check_param(h), check_param(dist_ah), check_param(dist_bh), check_param(dist_ch), check_param(dist_hd), check_param(dist_he), check_param(dist_hf));
}

template <class T>
void test_i(triangle<T> CR t) {
  point<T> i = tifa_libs::geo::center_I(t);

  T dist_ai = tifa_libs::geo::dist_PP(t.A, i), dist_bi = tifa_libs::geo::dist_PP(t.B, i), dist_ci = tifa_libs::geo::dist_PP(t.C, i);
  auto [a, b, c] = t.edges();
  T R = tifa_libs::geo::radius_O(t), r = tifa_libs::geo::radius_I(t);

  check_bool(is_eq(dist_ai * dist_ai / (b * c) + dist_bi * dist_bi / (c * a) + dist_ci * dist_ci / (a * b), (T)1), check_param(t), check_param(i), check_param(dist_ai), check_param(dist_bi), check_param(dist_ci), check_param(c), check_param(a), check_param(b));
  check_bool(is_eq(dist_ai * dist_bi * dist_ci, 4 * R * r * r), check_param(t), check_param(i), check_param(R), check_param(r), check_param(dist_ai), check_param(dist_bi), check_param(dist_ci));

  T ang_cai = tifa_libs::geo::ang2pi_PP(t.C - t.A, i - t.A), ang_iab = tifa_libs::geo::ang2pi_PP(i - t.A, t.B - t.A);
  T ang_abi = tifa_libs::geo::ang2pi_PP(t.A - t.B, i - t.B), ang_ibc = tifa_libs::geo::ang2pi_PP(i - t.B, t.C - t.B);
  T ang_bci = tifa_libs::geo::ang2pi_PP(t.B - t.C, i - t.C), ang_ica = tifa_libs::geo::ang2pi_PP(i - t.C, t.A - t.C);

  check_bool(is_eq(ang_cai, ang_iab), check_param(t), check_param(i), check_param(ang_cai), check_param(ang_iab));
  check_bool(is_eq(ang_abi, ang_ibc), check_param(t), check_param(i), check_param(ang_abi), check_param(ang_ibc));
  check_bool(is_eq(ang_bci, ang_ica), check_param(t), check_param(i), check_param(ang_bci), check_param(ang_ica));
}

template <class T>
void test_o(triangle<T> CR t) {
  point<T> o = tifa_libs::geo::center_O(t);

  T R = tifa_libs::geo::radius_O(t), diam = R * 2;
  T dist_ao = tifa_libs::geo::dist_PP(t.A, o), dist_bo = tifa_libs::geo::dist_PP(t.B, o), dist_co = tifa_libs::geo::dist_PP(t.C, o);

  check_bool(is_eq(R, dist_ao), check_param(t), check_param(R), check_param(dist_ao));
  check_bool(is_eq(R, dist_bo), check_param(t), check_param(R), check_param(dist_bo));
  check_bool(is_eq(R, dist_co), check_param(t), check_param(R), check_param(dist_co));

  auto [a, b, c] = t.edges();
  auto [A, B, C] = t.angles();
  T das = a / std::sin(A), dbs = b / std::sin(B), dcs = c / std::sin(C);

  check_bool(is_eq(diam, das), check_param(t), check_param(diam), check_param(das), check_param(a), check_param(A));
  check_bool(is_eq(diam, dbs), check_param(t), check_param(diam), check_param(dbs), check_param(b), check_param(B));
  check_bool(is_eq(diam, dcs), check_param(t), check_param(diam), check_param(dcs), check_param(c), check_param(C));

  T area = tifa_libs::geo::area_T_abc(a, b, c);
  T ds = std::sqrt(2 * area / (std::sin(A) * std::sin(B) * std::sin(C)));
  T ds2 = a * b * c / (2 * area);

  check_bool(is_eq(diam, ds), check_param(t), check_param(diam), check_param(ds), check_param(area), check_param(A), check_param(B), check_param(C));
  check_bool(is_eq(diam, ds2), check_param(t), check_param(diam), check_param(ds2), check_param(area), check_param(a), check_param(b), check_param(c));
}

template <class T>
void test_n(triangle<T> CR t) {
  point<T> n = tifa_libs::geo::center_N(t);
  point<T> o = tifa_libs::geo::center_O(t), h = tifa_libs::geo::center_H(t), g = tifa_libs::geo::center_G(t), i = tifa_libs::geo::center_I(t);

  check(n, mid_point(o, h), check_param(t), check_param(n), check_param(o), check_param(h));
  check_bool(is_zero(tifa_libs::geo::cross_unit(n, o, g)), check_param(t), check_param(n), check_param(o), check_param(g));

  T no = tifa_libs::geo::dist_PP(n, o), nh = tifa_libs::geo::dist_PP(n, h), ng = tifa_libs::geo::dist_PP(n, g);

  check_bool(is_eq(no, nh) && is_eq(nh, ng * 3), check_param(t), check_param(n), check_param(o), check_param(h), check_param(g), check_param(no), check_param(nh), check_param(ng));

  T R = tifa_libs::geo::radius_O(t), r = tifa_libs::geo::radius_I(t);
  T ni = tifa_libs::geo::dist_PP(n, i), oi = tifa_libs::geo::dist_PP(o, i);

  check_bool(is_eq(ni, R / 2 - r), check_param(t), check_param(n), check_param(i), check_param(ni), check_param(R), check_param(r));
  check_bool(is_eq(2 * R * ni, oi * oi), check_param(t), check_param(n), check_param(i), check_param(ni), check_param(oi), check_param(R));
}

template <class T>
void test_x(triangle<T> CR t) {
  point<T> x = tifa_libs::geo::center_X(t);
  point<T> uva = (t.A - x).do_unit(), uvb = (t.B - x).do_unit(), uvc = (t.C - x).do_unit();
  T ang_axb = std::abs(tifa_libs::geo::ang_PP(uva, uvb)), ang_bxc = std::abs(tifa_libs::geo::ang_PP(uvb, uvc)), ang_cxa = std::abs(tifa_libs::geo::ang_PP(uvc, uva));

  CEXP T _60 = pi_v<T> / 3, _120 = pi_v<T> / 1.5;

  check_bool((is_eq(ang_axb, _120) && is_eq(ang_bxc, _120) && is_eq(ang_cxa, _120)) ||
                 (is_eq(ang_axb, _60) && is_eq(ang_bxc, _60) && is_eq(ang_cxa, _120)) ||
                 (is_eq(ang_axb, _120) && is_eq(ang_bxc, _60) && is_eq(ang_cxa, _60)) ||
                 (is_eq(ang_axb, _60) && is_eq(ang_bxc, _120) && is_eq(ang_cxa, _60)),
             check_param(t), check_param(x), check_param(uva), check_param(uvb), check_param(uvc), check_param(ang_axb), check_param(ang_bxc), check_param(ang_cxa));
}

template <tifa_libs::arithm_c T>
void test(T lim) {
  tifa_libs::rand::Gen<T> g(std::is_signed_v<T> ? -lim : 0, lim);

  triangle<T> t(point<T>(g(), g()), point<T>(g(), g()), point<T>(g(), g()));

  test_e(t);
  test_g(t);
  test_h(t);
  test_i(t);
  test_o(t);
  test_n(t);
  test_x(t);
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<f64>(1e5); break;
    case tifa_libs::unittest::ts_example_01: test<f128>(1e5); break;
    case tifa_libs::unittest::ts_random_00: test<f64>(1e9); break;
    case tifa_libs::unittest::ts_random_01: test<f128>(1e9); break;
    case tifa_libs::unittest::ts_random_02: break;
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