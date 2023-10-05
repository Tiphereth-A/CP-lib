#ifndef TIFA_LIBS_GEO3D_POLYHEDRON
#define TIFA_LIBS_GEO3D_POLYHEDRON

#include "plane.hpp"

namespace tifa_libs::geo {

template <class FP>
struct polyhedron {
  struct phd_face {
    plane<FP> pl;
    // 邻接面 ID
    u32 nid[3];

    explicit constexpr phd_face(plane<FP> const &pl, u32 n1 = 0, u32 n2 = 0, u32 n3 = 0) : pl(pl), nid{n1, n2, n3} {}

    void bind(size_t n1, size_t n2, size_t n3) {
      nid[0] = n1;
      nid[1] = n2;
      nid[2] = n3;
    }
  };

  struct phd_edge {
    point3d<FP> p;
    // 邻接面 ID
    size_t fid;

    explicit constexpr phd_edge(point3d<FP> const &p, size_t f = 0) : p(p), fid(f) {}

    void bind(size_t f) { fid = f; }
  };

  vec<phd_face> vphn;

  explicit polyhedron() {}
};

}  // namespace tifa_libs::geo

#endif