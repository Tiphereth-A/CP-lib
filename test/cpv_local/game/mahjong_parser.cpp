// competitive-verifier: STANDALONE

#include "../../../src/game/mahjong/parser/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using namespace tifa_libs::literals;

vecp<u32, vec<mahjong_card>> mahjong_hand_data{
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

  auto parsed = mahjong_parser<14>(hand);
  bool win = any_of(parsed, [](auto CR hand) { return hand.win(); });

  auto f = [](auto& v) {
    vec<strn> ans;
    for (auto [melds, c] : v) {
      auto card = mahjong_card::decode(c);
      strn meld_str;
      switch (melds) {
        case MELDS_MJ::mian: meld_str = "mian"; break;
        case MELDS_MJ::bianl: meld_str = "bianl"; break;
        case MELDS_MJ::bianr: meld_str = "bianr"; break;
        case MELDS_MJ::kan: meld_str = "kan"; break;
        case MELDS_MJ::orphan: meld_str = "orphan"; break;
        case MELDS_MJ::pair: meld_str = "pair"; break;
        case MELDS_MJ::pair0: meld_str = "pair0"; break;
        case MELDS_MJ::bonus: meld_str = "bonus"; break;
        case MELDS_MJ::chow: meld_str = "chow"; break;
        case MELDS_MJ::pung: meld_str = "pung"; break;
        case MELDS_MJ::kong: meld_str = "kong"; break;
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
  for (u32 i = 0; i <= 18; ++i) {
    timer_(test(i));
  }
}