#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/game/mahjong_parser.hpp"

#include "../base.hpp"

using namespace tifa_libs;
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

std::stringstream single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  u32 kase = 0;
  strn s;
  while (true) {
    do std::getline(fin, s);
    while (s.empty());
    if (s[0] == '0') goto end__;
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
      // auto [__, mode, waiting, prepared] = p;
      // for (auto [r, s] : waiting) {
      //   auto c = game::mahjong_card::decode(s);
      //   std::cout << '(' << (u32)r << ' ' << c.rank << c.suit << ") ";
      // }
      // std::cout << "| ";
      // for (auto [r, s] : prepared) {
      //   auto c = game::mahjong_card::decode(s);
      //   std::cout << '(' << (u32)r << ' ' << c.rank << c.suit << ") ";
      // }
      // std::cout << std::endl;
      auto _ = p.improve_cards();
      ans.insert(ans.end(), _.begin(), _.end());
    }
    ss << "Case " << ++kase << ": ";
    if (ans = uniq(ans); ans.empty()) ss << "Not ready\n";
    else
      flt_ (u32, i, 0, (u32)ans.size()) ss << mp2[ans[i]] << " \n"[i + 1 == ans.size()];
  }

end__:;
  return ss;
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "11210", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  std::stringstream sgots = single_proceed(fin);
  strn got, want;
  while (true) {
    std::getline(sgots, got);
    std::getline(fans, want);
    if (got.empty() && want.empty()) break;
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want);
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: test("3"); break;
    case unittest::TC::random_01: test("4"); break;
    case unittest::TC::random_02: test("5"); break;
    case unittest::TC::random_03: test("6"); break;
    case unittest::TC::random_04: test("7"); break;
    case unittest::TC::random_05: test("8"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}