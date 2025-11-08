#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/game/mahjong_parser.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using namespace tifa_libs::game::literals;

vecp<u32, vec<game::mahjong_card>> mahjong_hand_data{
    {5, {1_mjs, 2_mjs, 5_mjs, 6_mjs, 8_mjs, 9_mjs, 1_mjm, 2_mjm, 5_mjm, 6_mjm, 8_mjm, 9_mjm, 1_mjp, 2_mjp}},
    {4, {1_mjs, 1_mjs, 4_mjs, 4_mjs, 7_mjs, 7_mjs, 1_mjm, 1_mjm, 4_mjm, 4_mjm, 7_mjm, 7_mjm, 1_mjp, 1_mjp}},
    {3, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 4_mjs, 4_mjs, 7_mjs, 7_mjs, 1_mjm, 1_mjm, 4_mjm, 4_mjm, 7_mjm, 7_mjm}},
    {2, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 2_mjs, 1_mjm, 1_mjm, 4_mjm, 4_mjm, 7_mjm, 7_mjm}},
    {1, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 2_mjs, 1_mjm, 1_mjm, 1_mjm, 1_mjm, 4_mjm, 4_mjm}},
    {2, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 2_mjs, 1_mjm, 1_mjm, 1_mjm, 1_mjm, 4_mjm, 5_mjm}},
    {3, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 4_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjm, 1_mjm, 1_mjm, 1_mjm, 4_mjm, 5_mjm}},
    {4, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 4_mjs, 5_mjs, 8_mjs, 9_mjs, 1_mjm, 2_mjm, 5_mjm, 6_mjm, 8_mjm, 9_mjm}},
    {3, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 4_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjm, 2_mjm, 5_mjm, 6_mjm, 8_mjm, 9_mjm}},
    {3, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 2_mjs, 1_mjm, 2_mjm, 5_mjm, 6_mjm, 8_mjm, 9_mjm}},
    {5, {1_mjs, 1_mjs, 1_mjs, 1_mjs, 4_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjm, 4_mjm, 7_mjm, 1_mjp, 4_mjp, 7_mjp}},
    {3, {1_mjz, 1_mjz, 1_mjz, 1_mjz, 2_mjz, 2_mjz, 2_mjz, 2_mjz, 3_mjz, 3_mjz, 3_mjz, 3_mjz, 4_mjz, 4_mjz}},
    {3, {1_mjz, 1_mjz, 1_mjz, 1_mjz, 2_mjz, 2_mjz, 2_mjz, 2_mjz, 3_mjz, 3_mjz, 3_mjz, 3_mjz, 4_mjz, 7_mjz}},
    {2, {1_mjm, 1_mjm, 1_mjm, 1_mjm, 1_mjz, 1_mjz, 1_mjz, 1_mjz, 2_mjz, 2_mjz, 2_mjz, 2_mjz, 3_mjz, 3_mjz}},
    {3, {1_mjm, 1_mjm, 1_mjm, 1_mjm, 1_mjz, 1_mjz, 1_mjz, 1_mjz, 2_mjz, 2_mjz, 2_mjz, 2_mjz, 3_mjz, 4_mjz}},
    {1, {1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 3_mjs, 3_mjs, 3_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjz, 2_mjz}},
    {1, {1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 3_mjs, 3_mjs, 3_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjp, 2_mjp}},
    {0, {1_mjs, 1_mjs, 1_mjs, 2_mjs, 2_mjs, 2_mjs, 3_mjs, 3_mjs, 3_mjs, 4_mjs, 4_mjs, 4_mjs, 1_mjp, 1_mjp}},
    {9, {2_mjm, 5_mjm, 8_mjm, 2_mjp, 5_mjp, 8_mjp, 2_mjs, 5_mjs, 8_mjs, 1_mjz, 2_mjz, 3_mjz, 4_mjz, 7_mjz}},
};

void test(u32 n) {
  auto [step, hand] = mahjong_hand_data[n];

  auto parsed = game::mahjong_parser<14>(hand);
  bool win = any_of(parsed, [](auto CR hand) { return hand.win(); });

  auto f = [](auto& v) {
    vec<strn> ans;
    for (auto [melds, c] : v) {
      auto card = game::mahjong_card::decode(c);
      strn meld_str;
      switch (melds) {
        case game::MELDS_MJ::mian: meld_str = "mian"; break;
        case game::MELDS_MJ::bianl: meld_str = "bianl"; break;
        case game::MELDS_MJ::bianr: meld_str = "bianr"; break;
        case game::MELDS_MJ::kan: meld_str = "kan"; break;
        case game::MELDS_MJ::orphan: meld_str = "orphan"; break;
        case game::MELDS_MJ::pair: meld_str = "pair"; break;
        case game::MELDS_MJ::pair0: meld_str = "pair0"; break;
        case game::MELDS_MJ::bonus: meld_str = "bonus"; break;
        case game::MELDS_MJ::chow: meld_str = "chow"; break;
        case game::MELDS_MJ::pung: meld_str = "pung"; break;
        case game::MELDS_MJ::kong: meld_str = "kong"; break;
      }
      ans.push_back(std::format("({}:{}{})", meld_str, card.rank, card.suit));
    }
    return ans;
  };
  vvec<strn> prepared, waiting;
  for (auto CR hand : parsed) {
    prepared.push_back(f(hand.prepared));
    waiting.push_back(f(hand.waiting));
  }

  check(win, !step, check_param(n), check_param(prepared), check_param(waiting));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(0), test(12); break;
    case unittest::TC::example_01: test(1), test(13); break;
    case unittest::TC::random_00: test(2), test(14); break;
    case unittest::TC::random_01: test(3), test(15); break;
    case unittest::TC::random_02: test(4), test(16); break;
    case unittest::TC::random_03: test(5), test(17); break;
    case unittest::TC::random_04: test(6), test(18); break;
    case unittest::TC::random_05: test(7); break;
    case unittest::TC::random_06: test(8); break;
    case unittest::TC::random_07: test(9); break;
    case unittest::TC::random_08: test(10); break;
    case unittest::TC::random_09: test(11); break;
    default: break;
  }

  unittest::post_test();
}