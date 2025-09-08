#ifndef TIFALIBS_OPT_SIMPLEX
#define TIFALIBS_OPT_SIMPLEX

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

template <class T = f64>
struct LPSolver {
#define ltj(X) \
  if (!~s || std::make_pair(X[j], N[j]) < std::make_pair(X[s], N[s])) s = j
  static CEXP T inf = 1 / .0;
  int m, n;   // # m = contraints, # n = variables
  veci N, B;  // N[j] = non-basic variable (j-th column), = 0
  vvec<T> D;  // B[j] = basic variable (j-th row)
  CEXP LPSolver(vvec<T> CR A, vec<T> CR b, vec<T> CR c) NE : m{sz(b)}, n{sz(c)}, N(n + 1), B(m), D(m + 2, vec<T>(n + 2)) {
    flt_ (int, i, 0, m)
      flt_ (int, j, 0, n) D[i][j] = A[i][j];
    flt_ (int, i, 0, m) B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
    // B[i]: basic variable for each constraint
    // D[i][n]: artificial variable for testing feasibility
    flt_ (int, j, 0, n) N[j] = j, D[m][j] = -c[j];
    // D[m] stores negation of objective,
    // which we want to minimize
    N[n] = -1;
    D[m + 1][n] = 1;  // to find initial feasible
  }  // solution, minimize artificial variable
  CEXP void pivot(int r, int s) NE {  // swap B[r] (row)
    T inv = 1 / D[r][s];              // with N[r] (column)
    for (int i = 0; i <= m + 1; ++i)
      if (i != r && abs(D[i][s]) > eps_v<T>) {
        T binv = D[i][s] * inv;
        for (int j = 0; j < (n + 2); ++j)
          if (j != s) D[i][j] -= D[r][j] * binv;
        D[i][s] = -binv;
      }
    D[r][s] = 1;
    for (int j = 0; j < (n + 2); ++j) D[r][j] *= inv;  // scale r-th row
    swap(B[r], N[s]);
  }
  CEXP bool simplex(int phase) NE {
    int x = m + phase - 1;
    while (1) {  // if phase=1, ignore artificial variable
      int s = -1;
      flt_ (int, j, 0, n + 1)
        if (N[j] != -phase) ltj(D[x]);
      // find most negative col for nonbasic (NB) variable
      if (D[x][s] >= -eps_v<T>) return 1;
      // can't get better sol by increasing NB variable
      int r = -1;
      flt_ (int, i, 0, m) {
        if (D[i][s] <= eps_v<T>) continue;
        if (!~r || std::make_pair(D[i][n + 1] / D[i][s], B[i]) < std::make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
        // find smallest positive ratio
      }  // -> max increase in NB variable
      if (!~r) return 0;  // objective is unbounded
      pivot(r, s);
    }
  }
  CEXP T solve(vec<T>& x) NE {  // 1. check if x=0 feasible
    int r = 0;
    for (int i = (1); i < m; ++i)
      if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -eps_v<T>) {  // if not, find feasible start
      pivot(r, n);                  // make artificial variable basic
      assert(simplex(2));           // I think this will always be true??
      if (D[m + 1][n + 1] < -eps_v<T>) return -inf;
      // D[m+1][n+1] is max possible value of the negation of
      // artificial variable, optimal value should be zero
      // if exists feasible solution
      flt_ (int, i, 0, m)
        if (!~B[i]) {  // artificial var basic
          int s = 0;
          for (int j = (1); j <= n; ++j) ltj(D[i]);  // -> nonbasic
          pivot(i, s);
        }
    }
    bool ok = simplex(1);
    x = vec<T>(n);
    flt_ (int, i, 0, m)
      if (B[i] < n) x[B[i]] = D[i][n + 1];
    retif_((ok), D[m][n + 1], inf);
  }
};
#undef ltj

}  // namespace tifa_libs::opt

#endif