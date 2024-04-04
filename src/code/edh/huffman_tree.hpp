#ifndef TIFALIBS_EDH_HUFFMAN_TREE
#define TIFALIBS_EDH_HUFFMAN_TREE

#include "../util/util.hpp"

namespace tifa_libs {

template <class T = u64>
class huffman {
  struct YYZ {
    T weight;
    vecu ch;
    constexpr YYZ(T weight = T{}, u32 child_cnt = 0) : weight(weight), ch(child_cnt) {}
  };
  u32 cnt_w, cnt_l, ch_sz;
  vec<YYZ> data;

  template <class Res, class Op>
  constexpr vec<Res> run(Op &&operate) const {
    vec<Res> ret(cnt_w);
    std::queue<std::pair<u32, Res>> q;
    q.emplace(data.size() - 1, Res{});
    while (!q.empty()) {
      auto [now_idx, now_code] = q.front();
      auto &ch = data[now_idx].ch;
      q.pop();
      for (u32 i = 0; i < ch_sz; ++i) {
        auto &&next_child = ch[i];
        if (next_child < cnt_l) {
          if (next_child < cnt_w) ret[next_child] = operate(now_code, i);
          continue;
        } else q.emplace(next_child, operate(now_code, i));
      }
    }
    return ret;
  }

 public:
  explicit constexpr huffman(vec<T> const &weights, u32 child_sz = 2) : cnt_w((u32)weights.size()), cnt_l(), ch_sz(child_sz), data() {
    assert(1 < child_sz && child_sz < weights.size());
    for (T now : weights) data.emplace_back(now);
    for (u32 i = 0, iend = ((ch_sz - 1) - ((cnt_w - 1) % (ch_sz - 1))) % (ch_sz - 1); i < iend; ++i) data.emplace_back();
    cnt_l = (u32)data.size();
    pqg<std::pair<T, u32>> q;
    for (u32 i = 0; i < data.size(); ++i) q.emplace(data[i].weight, i);
    while (q.size() > 1) {
      data.emplace_back(T{}, ch_sz);
      for (u32 i = 0; i < ch_sz; ++i) {
        auto [now_weight, now_idx] = q.top();
        data.back().weight += now_weight;
        data.back().ch[i] = now_idx;
        q.pop();
      }
      q.emplace(data.back().weight, data.size() - 1);
    }
  }

  constexpr vec<strn> encode(strnv char_set = "01") const {
    assert(char_set.size() == ch_sz);
    return run<strn>([&](strn const &pre_code, u32 idx) { return pre_code + char_set[idx]; });
  }
  constexpr vecu depths() const {
    return run<u32>([](u32 const &pre_depth, u32) { return pre_depth + 1; });
  }
};

}  // namespace tifa_libs

#endif