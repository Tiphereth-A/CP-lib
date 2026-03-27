// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/11210

#include "../../../src/game/mahjong/parser/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using namespace tifa_libs::game::literals;

static auto [mp, mp2] = [] {
#define _(n, i, j) {#n #i, n##_mj##j}
#define __(i, j) _(1, i, j), _(2, i, j), _(3, i, j), _(4, i, j), _(5, i, j), _(6, i, j), _(7, i, j), _(8, i, j), _(9, i, j)
  std::map<strn, game::mahjong_card> mp{
      __(T, p),
      __(S, s),
      __(W, m),
      {"DONG", 1_mjz},
      {"NAN", 2_mjz},
      {"XI", 3_mjz},
      {"BEI", 4_mjz},
      {"ZHONG", 5_mjz},
      {"FA", 6_mjz},
      {"BAI", 7_mjz},
  };
#undef __
#undef _

  arr<strn, 45> mp2;
  for (auto CR[k, v] : mp) mp2[v.encode()] = k;
  return std::make_pair(mp, mp2);
}();

int main() {
  cout << std::fixed << std::setprecision(2);

  u32 kase = 0;
  strn s;
  while (std::getline(cin, s) && s[0] != '0') {
    vec<game::mahjong_card> hand;
    hand.reserve(13);
    {
      std::stringstream ss;
      ss << s;
      while (ss >> s) hand.push_back(mp[s]);
    }
    vecu ans;
    auto res = game::mahjong_parser<13>(hand);
    for (auto CR p : res) {
      if (!p.win()) continue;
      auto _ = p.improve_cards();
      ans.insert(ans.end(), _.begin(), _.end());
    }
    cout << "Case " << ++kase << ": ";
    if (ans = uniq(ans); ans.empty()) cout << "Not ready\n";
    else
      flt_ (u32, i, 0, (u32)ans.size()) cout << mp2[ans[i]] << " \n"[i + 1 == ans.size()];
  }
}