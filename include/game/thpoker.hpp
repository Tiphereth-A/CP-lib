#ifndef TIFALIBS_GAME_THPOKER
#define TIFALIBS_GAME_THPOKER

#include "poker_data.hpp"

namespace tifa_libs::game {

// clang-format off
enum class HAND_VALUES_THP { high_card, pair, two_pairs, three_of_a_kind, straight, flush, full_house, four_of_a_kind, straight_flush, royal_flush };
// clang-format on

using thpoker_values_t = std::pair<HAND_VALUES_THP, vecu>;
CEXP thpoker_values_t thpoker_values(vec<poker_card> CR hand) NE {
  assert(hand.size() == 5);
  bool const is_flush = all_of(hand, [&](poker_card c) { return c.suit == hand[0].suit; });
  auto const ranks = [&] {
    vecu ranks;
    for (auto& [r, s] : hand) ranks.push_back(r);
    sort(ranks, greater{});
    return ranks;
  }();
  bool const is_royal = ranks == vecu{14, 5, 4, 3, 2};
  bool const is_straight = [&] {
    if (!is_royal)
      flt_ (u32, i, 1, 5)
        if (ranks[i] != ranks[i - 1] - 1) return false;
    return true;
  }();

  auto const cnt_rank = [&] {
    vecptu cnts;
    arr<u32, 15> _;
    for (auto r : ranks) ++_[r];
    flt_ (u32, i, 2, 15)
      if (_[i]) cnts.emplace_back(_[i], i);
    sort(cnts, greater{});
    return cnts;
  }();
  auto uniqed = [&](itlu l) {
    vecu uniqed(l);
    for (auto [c, r] : cnt_rank)
      if (c == 1) uniqed.push_back(r);
    sort(uniqed.begin() + (u32)l.size(), uniqed.end(), greater{});
    return uniqed;
  };

  if (is_royal && is_flush) return {HAND_VALUES_THP::royal_flush, {}};
  if (is_straight && is_flush) return {HAND_VALUES_THP::straight_flush, {ranks[0]}};
  if (cnt_rank[0].first == 4) return {HAND_VALUES_THP::four_of_a_kind, {cnt_rank[0].second, cnt_rank[1].second}};
  if (cnt_rank[0].first == 3 && cnt_rank[1].first == 2) return {HAND_VALUES_THP::full_house, {cnt_rank[0].second, cnt_rank[1].second}};
  if (is_flush) return {HAND_VALUES_THP::flush, ranks};
  if (is_straight) return {HAND_VALUES_THP::straight, {ranks[0]}};
  if (cnt_rank[0].first == 3) return {HAND_VALUES_THP::three_of_a_kind, uniqed({cnt_rank[0].second})};
  if (cnt_rank[0].first == 2 && cnt_rank[1].first == 2) return {HAND_VALUES_THP::two_pairs, uniqed({cnt_rank[0].second, cnt_rank[1].second})};
  if (cnt_rank[0].first == 2) return {HAND_VALUES_THP::pair, uniqed({cnt_rank[0].second})};
  return {HAND_VALUES_THP::high_card, ranks};
}

}  // namespace tifa_libs::game

#endif