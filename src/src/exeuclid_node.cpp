// let f(x) = floor((p * x + r) / q)
// @param u (REQUIRED) count of horizontal lines have been crossed
// @param r (REQUIRED) count of vertical lines have been crossed
// @param i sum_i i (needed by i_f)
// @param f sum_i i f(i)
// @param sqr_f sum_i f^2(i)
// @param i_f sum_i i*f(i) (need i)
template <class T>
struct exeuclid_node {
  T u, r;
  T i, f, sqr_f, i_f;
  exeuclid_node(T u = 0, T r = 0, T i = 0, T f = 0, T sqr_f = 0, T i_f = 0) : u(u), r(r), i(i), f(f), sqr_f(sqr_f), i_f(i_f) {}
  friend exeuclid_node operator*(exeuclid_node const &l, exeuclid_node const &r) {
    return {l.u + r.u,
            l.r + r.r,
            l.i + r.i + l.r * r.r,
            l.f + r.f + l.u * r.r,
            l.sqr_f + r.sqr_f + l.u * l.u * r.r + 2 * l.u * r.f,
            l.i_f + r.i_f + l.u * l.r * r.r + l.u * r.i + l.r * r.f};
  }
};
