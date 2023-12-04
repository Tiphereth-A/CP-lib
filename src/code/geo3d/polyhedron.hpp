#ifndef TIFALIBS_GEO3D_POLYHEDRON
#define TIFALIBS_GEO3D_POLYHEDRON

#include "plane.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polyhedron {
  struct phd_face {
    plane<FP> pl;
    // 邻接面 ID
    u32 nid[3];

    explicit constexpr phd_face(plane<FP> const &pl, u32 n1 = 0, u32 n2 = 0, u32 n3 = 0) : pl(pl), nid{n1, n2, n3} {}

    void bind(u32 n1, u32 n2, u32 n3) {
      nid[0] = n1;
      nid[1] = n2;
      nid[2] = n3;
    }
  };

  struct phd_edge {
    point3d<FP> p;
    // 邻接面 ID
    u32 fid;

    explicit constexpr phd_edge(point3d<FP> const &p, u32 f = 0) : p(p), fid(f) {}

    void bind(u32 f) { fid = f; }
  };

  vec<phd_face> vphn;

  explicit polyhedron() {}
};

}  // namespace tifa_libs::geo

#endif