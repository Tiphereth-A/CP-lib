#ifndef TIFALIBS_GEO3D_CVH3D
#define TIFALIBS_GEO3D_CVH3D

#include "../math/kahan.hpp"
#include "dist3_pl.hpp"
#include "dist3_pp.hpp"
#include "planev.hpp"
#include "rel_plp.hpp"
#include "sdist3_plp.hpp"

namespace tifa_libs::geo {

template <class FP>
class cvh3d {
  struct facet {
    u32 n[3], id, vistime = 0;
    bool isdel = 0;
    planev<FP> p;
    u32 pid[3];

    CEXP facet() {}
    CEXP facet(u32 id, vec<point3d<FP>> CR vp, u32 id0, u32 id1, u32 id2) : id(id), p(vp[id0], vp[id1], vp[id2]), pid{id0, id1, id2} {}
    CEXP facet(vec<point3d<FP>> CR vp, u32 id0, u32 id1, u32 id2) : facet(0, vp, id0, id1, id2) {}
    CEXP void in(u32 n1, u32 n2, u32 n3) { n[0] = n1, n[1] = n2, n[2] = n3; }
  };
  u32 tm = 0, idx = 0;
  math::kahan<FP> suf_area = 0;

 public:
  //! 1-indexed
  vec<facet> faces;
  //! 1-indexed, no co-linear or co-plane
  explicit cvh3d(vec<point3d<FP>> CR vp) {
    faces.emplace_back(vp, 0, 0, 0), faces[0].isdel = 1;
    vvecu ptsid(5);
    {
#define v(n, i) vp[n##id[i]]
      u32 pid[6]{1, 1, 1, 1, 1, 1};
      flt_ (u32, i, 2, (u32)vp.size()) {
        if (is_gt(vp[i].x, v(p, 0).x)) pid[0] = i;
        if (is_gt(v(p, 1).x, vp[i].x)) pid[1] = i;
        if (is_gt(vp[i].y, v(p, 2).y)) pid[2] = i;
        if (is_gt(v(p, 3).y, vp[i].y)) pid[3] = i;
        if (is_gt(vp[i].z, v(p, 4).z)) pid[4] = i;
        if (is_gt(v(p, 5).z, vp[i].z)) pid[5] = i;
      }
      u32 sid[4]{pid[0], pid[0], pid[0], pid[0]};
      flt_ (u32, i, 0, 6)
        flt_ (u32, j, i + 1, 6)
          if (is_gt(dist3_PP(v(p, i), v(p, j)), dist3_PP(v(s, 0), v(s, 1)))) sid[0] = pid[i], sid[1] = pid[j];
      flt_ (u32, i, 0, 6)
        if (is_gt(dist3_PL(v(p, i), {v(s, 0), v(s, 1)}), dist3_PL(v(s, 2), {v(s, 0), v(s, 1)}))) sid[2] = pid[i];
      flt_ (u32, i, 1, (u32)vp.size())
        if (is_gt(abs(sdist3_PlP(planev<FP>{v(s, 0), v(s, 1), v(s, 2)}, vp[i])), abs(sdist3_PlP(planev<FP>{v(s, 0), v(s, 1), v(s, 2)}, v(s, 3))))) sid[3] = i;
      if (is_neg(sdist3_PlP(planev<FP>{v(s, 0), v(s, 1), v(s, 2)}, v(s, 3)))) swap(sid[1], sid[2]);
      faces.emplace_back(1, vp, sid[0], sid[2], sid[1]), faces.emplace_back(2, vp, sid[0], sid[1], sid[3]);
      faces.emplace_back(3, vp, sid[1], sid[2], sid[3]), faces.emplace_back(4, vp, sid[2], sid[0], sid[3]);
      faces[1].in(4, 3, 2), faces[2].in(1, 3, 4), faces[3].in(1, 4, 2), faces[4].in(1, 2, 3);
      flt_ (u32, i, 1, (u32)vp.size()) {
        if (vp[i] == v(s, 0) || vp[i] == v(s, 1) || vp[i] == v(s, 2) || vp[i] == v(s, 3)) continue;
        fle_ (u32, j, 1, 4)
          if (relation_PlP(faces[j].p, vp[i]) == above_plp) {
            ptsid[j].push_back(i);
            break;
          }
      }
      idx = 1;
#undef v
    }
    struct edge {
      u32 netid, facetid;
    };
    vec<edge> e1(vp.size()), e2(vp.size());
    vecu vistime(vp.size()), resfdel(vp.size()), resfnew(vp.size()), resptid(vp.size());
    auto horizon = [&](auto &&f, u32 id, point3d<FP> CR p) -> u32 {
      if (relation_PlP(faces[id].p, p) != above_plp) return 0;
      if (faces[id].vistime == tm) return -1_u32;
      faces[id].vistime = tm, faces[id].isdel = 1, resfdel.push_back(faces[id].id);
      u32 ret = -2_u32;
      flt_ (u32, i, 0, 3)
        if (u32 res = f(f, faces[id].n[i], p); !res) {
          u32 pt[2]{faces[id].pid[i], faces[id].pid[(i + 1) % 3]};
          flt_ (u32, j, 0, 2)
            if (vistime[pt[j]] != tm) vistime[pt[j]] = tm, e1[pt[j]].netid = pt[j ^ 1], e1[pt[j]].facetid = faces[id].n[i];
            else e2[pt[j]].netid = pt[j ^ 1], e2[pt[j]].facetid = faces[id].n[i];
          ret = pt[0];
        } else if ((int)res > 0) ret = res;
      return ret;
    };
    std::queue<u32> que({idx});
    for (auto i : faces[idx].n) que.push(i);
    u32 snew = 0;
    while (!que.empty()) {
      u32 nf = que.front();
      que.pop();
      if (faces[nf].isdel) continue;
      if (ptsid[nf].empty()) {
        snew = nf;
        continue;
      }
      u32 pid = ptsid[nf][0];
      point3d<FP> p = vp[pid];
      flt_ (u32, i, 1, (u32)ptsid[nf].size())
        if (is_gt(sdist3_PlP(faces[nf].p, vp[ptsid[nf][i]]), sdist3_PlP(faces[nf].p, p))) p = vp[pid = ptsid[nf][i]];
      ++tm, resfdel.clear();
      u32 s = horizon(horizon, nf, p);
      ++tm, resfnew.clear();
      u32 from = 0, lastf = 0, fstf = 0;
      while (vistime[s] != tm) {
        vistime[s] = tm;
        u32 net, f, fnew;
        if (e1[s].netid == from) net = e2[s].netid, f = e2[s].facetid;
        else net = e1[s].netid, f = e1[s].facetid;
        u32 pt1 = -1_u32, pt2 = -1_u32, pt1id = -1_u32, pt2id = -1_u32;
        flt_ (u32, i, 0, 3) {
          if (vp[s] == faces[f].p.get(i)) pt1 = i, pt1id = s;
          if (vp[net] == faces[f].p.get(i)) pt2 = i, pt2id = net;
        }
        if ((pt1 + 1) % 3 != pt2) swap(pt1, pt2);
        faces.emplace_back(vp, pt2id, pt1id, pid), faces[fnew = u32(faces.size() - 1)].id = u32(faces.size() - 1);
        if (ptsid.push_back(vecu()), resfnew.push_back(fnew), faces[faces[fnew].n[0] = f].n[pt1] = fnew; lastf) {
          if (*faces[fnew].p.v == *faces[lastf].p.u) faces[fnew].n[1] = lastf, faces[lastf].n[2] = fnew;
          else faces[fnew].n[2] = lastf, faces[lastf].n[1] = fnew;
        } else fstf = fnew;
        lastf = fnew, from = s, s = net;
      }
      if (*faces[fstf].p.v == *faces[lastf].p.u) faces[fstf].n[1] = lastf, faces[lastf].n[2] = fstf;
      else faces[fstf].n[2] = lastf, faces[lastf].n[1] = fstf;
      for (resptid.clear(); auto i : resfdel) std::ranges::move(ptsid[i], std::back_inserter(resptid)), ptsid[i].clear();
      for (auto i : resptid) {
        if (vp[i] == p) continue;
        for (auto j : resfnew)
          if (relation_PlP(faces[j].p, vp[i]) == above_plp) {
            ptsid[j].push_back(i);
            break;
          }
      }
      for (auto i : resfnew) que.push(i);
    }
    idx = snew;
  }
  template <class F>
  requires requires(F op, math::kahan<FP> &v, planev<FP> p) { op(v, p); }
  CEXP void dfs(F &&op) {
    auto f = [&](auto &&f, u32 nf) -> void {
      if (faces[nf].vistime == tm) return;
      for (faces[nf].vistime = tm, op(suf_area, faces[nf].p); auto i : faces[nf].n) f(f, i);
    };
    ++tm, f(f, idx);
  }
  CEXP FP surface_area() {
    if (!is_zero((FP)suf_area)) return suf_area;
    return dfs([](math::kahan<FP> &v, planev<FP> p) { v += p.area(); }), suf_area;
  }
};

}  // namespace tifa_libs::geo

#endif