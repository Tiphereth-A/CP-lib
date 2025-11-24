#ifndef TIFALIBS_GAME_MAHJONG_PARSER
#define TIFALIBS_GAME_MAHJONG_PARSER

#include "../edh/discretization.hpp"
#include "mahjong_data.hpp"

namespace tifa_libs::game {

// clang-format off
// bianl: 89 waiting 7. bianr: 12 waiting 3. pair0: pair which cannot be improved
enum class MELDS_MJ: u8 { mian, bianl, bianr, kan, orphan, pair0, pair, bonus, chow, pung, kong };
// clang-format on
enum class RULE_MJ : u32 {
  enable_kong = 1,
  enable_13terminal = 2,
  enable_7pairs = 4
};

struct mahjong_hand {
  // clang-format off
  enum class MODE_MH: u8 { normal_13, normal_14, pairs7_13, pairs7_14, terminal13_13, terminal13_14 };
  // clang-format on

  u32 max_card_per_kind;
  MODE_MH mode;
  // eye in {@code waiting} if mode == normal, otherwise in {@code prepared}
  vecp<MELDS_MJ, u32> waiting, prepared;

  CEXP auto operator<=>(mahjong_hand CR) CNE = default;
  CEXP bool operator==(mahjong_hand CR) CNE = default;

  [[nodiscard]] CEXP arr<u32, 45> get_counter() CNE {
    arr<u32, 45> counter{};
    for (auto [melds, c] : waiting) switch (melds) {
        case MELDS_MJ::mian:
        case MELDS_MJ::bianl:
        case MELDS_MJ::bianr: ++counter[c], ++counter[c + 1]; break;
        case MELDS_MJ::kan: ++counter[c], ++counter[c + 2]; break;
        case MELDS_MJ::orphan: ++counter[c]; break;
        case MELDS_MJ::pair0:
        case MELDS_MJ::pair: counter[c] += 2; break;
        default: assert(false);
      }
    for (auto [melds, c] : prepared) switch (melds) {
        case MELDS_MJ::bonus:
        case MELDS_MJ::orphan: ++counter[c]; break;
        case MELDS_MJ::pair: counter[c] += 2; break;
        case MELDS_MJ::chow: ++counter[c], ++counter[c + 1], ++counter[c + 2]; break;
        case MELDS_MJ::pung: counter[c] += 3; break;
        case MELDS_MJ::kong: counter[c] += 4; break;
        default: assert(false);
      }
    return counter;
  }
  CEXP bool win() CNE {
    switch (mode) {
      case MODE_MH::pairs7_14:
      case MODE_MH::pairs7_13: return prepared.size() >= 6;
      case MODE_MH::terminal13_14: return prepared.size() == 13;
      case MODE_MH::terminal13_13: return prepared.size() == 13 || (prepared.size() == 12 && any_of(prepared, [](auto CR p) { return p.first == MELDS_MJ::pair; }));
      case MODE_MH::normal_14: return prepared.size() == 4 && any_of(waiting, [](auto CR p) { return p.first == MELDS_MJ::pair || p.first == MELDS_MJ::pair0; });
      case MODE_MH::normal_13: {
        if (prepared.size() == 4) return true;
        if (waiting.size() > 2 || prepared.size() < 3) return false;
        u32 cnt_pair = 0, cnt_bmk = 0;
        for (auto CR[meld, _] : waiting)
          if (meld == MELDS_MJ::pair || meld == MELDS_MJ::pair0) ++cnt_pair;
          else if (meld != MELDS_MJ::orphan) ++cnt_bmk;
        return cnt_pair == 2 || (cnt_pair == 1 && cnt_bmk == 1);
      }
    }
    assert(false);
  }
  CEXP vecu improve_cards() CNE {
    if (mode == MODE_MH::terminal13_13 || mode == MODE_MH::terminal13_14) {
      vecb vis(34);
      u32 p = 34;
      for (auto CR[meld, c] : prepared)
        if (vis[c] = true; meld == MELDS_MJ::pair) {
          p = c;
          break;
        }
      if (p == 34) return {0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33};
      vecu ans;
      for (ans.reserve(13); auto c : vecu{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33})
        if (!vis[c]) ans.push_back(c);
      return ans;
    }
    if (mode == MODE_MH::pairs7_13 || mode == MODE_MH::pairs7_14) {
      vecu ans;
      for (auto CR[_, c] : waiting) ans.push_back(c);
      return ans;
    }
    auto cnt_pair = count_if(waiting, [](auto CR p) { return p.first == MELDS_MJ::pair || p.first == MELDS_MJ::pair0; });
    vecb vis(34);
    for (auto [melds, c] : waiting) switch (melds) {
        case MELDS_MJ::mian: vis[c - 1] = vis[c + 2] = true; break;
        case MELDS_MJ::bianl: vis[c - 1] = true; break;
        case MELDS_MJ::bianr: vis[c + 2] = true; break;
        case MELDS_MJ::kan: vis[c + 1] = true; break;
        case MELDS_MJ::orphan: vis[c] = true; break;
        case MELDS_MJ::pair0: break;
        case MELDS_MJ::pair:
          if (cnt_pair > 1) vis[c] = true;
          break;
        default: assert(false);
      }
    auto counter = get_counter();
    flt_ (u32, i, 0, 34)
      if (counter[i] >= max_card_per_kind) vis[i] = false;
    vecu cards;
    flt_ (u32, i, 0, 34)
      if (vis[i]) cards.push_back(i);
    return cards;
  }
};

template <u32 cards = 14, u32 config = 0>
CEXP auto mahjong_parser(vec<mahjong_card> hand, u32 max_card_per_kind = 4) NE {
  static_assert(cards == 13 || cards == 14);
  CEXP bool enable_kong = config & (u32)RULE_MJ::enable_kong;
  CEXP bool enable_13terminal = config & (u32)RULE_MJ::enable_13terminal;
  CEXP bool enable_7pairs = config & (u32)RULE_MJ::enable_7pairs;
  CEXP auto normal = cards == 13 ? mahjong_hand::MODE_MH::normal_13 : mahjong_hand::MODE_MH::normal_14;
  CEXP auto pairs7 = cards == 13 ? mahjong_hand::MODE_MH::pairs7_13 : mahjong_hand::MODE_MH::pairs7_14;
  CEXP auto terminal13 = cards == 13 ? mahjong_hand::MODE_MH::terminal13_13 : mahjong_hand::MODE_MH::terminal13_14;
  using record_t = vecp<MELDS_MJ, u32>;
  struct guard {
    CEXP guard(record_t& target, arr<u8, 45>& counter, u32& sum_counter, u32 card, MELDS_MJ type) NE : target(target), counter(counter), sum_counter(sum_counter), card(card) {
      switch (type) {
        case MELDS_MJ::orphan: diff0 = 1; break;
        case MELDS_MJ::mian:
        case MELDS_MJ::bianl:
        case MELDS_MJ::bianr: diff0 = diff1 = 1; break;
        case MELDS_MJ::kan: diff0 = diff2 = 1; break;
        case MELDS_MJ::pair0:
        case MELDS_MJ::pair: diff0 = 2; break;
        case MELDS_MJ::chow: diff0 = diff1 = diff2 = 1; break;
        case MELDS_MJ::pung: diff0 = 3; break;
        case MELDS_MJ::kong: diff0 = 4; break;
        default: assert(false);
      }
#pragma GCC diagnostic ignored "-Wconversion"
      target.emplace_back(type, card), counter[card] -= diff0, counter[card + 1] -= diff1, counter[card + 2] -= diff2, sum_counter -= diff0 + diff1 + diff2;
    }
    CEXP ~guard() NE { target.pop_back(), counter[card] += diff0, counter[card + 1] += diff1, counter[card + 2] += diff2, sum_counter += diff0 + diff1 + diff2; }
#pragma GCC diagnostic warning "-Wconversion"
    guard(guard CR) = delete;
    guard& operator=(guard CR) = delete;
    guard(guard&&) = delete;
    guard& operator=(guard&&) = delete;

    record_t& target;
    arr<u8, 45>& counter;
    u32& sum_counter;
    u32 card, diff0 = 0, diff1 = 0, diff2 = 0;
  };
  if CEXP (enable_kong) assert(max_card_per_kind >= 4);
  else assert(max_card_per_kind >= 3);

  vec<mahjong_hand> ans;
  record_t base;
  sort(hand);
  while (!hand.empty() && hand.back().is_bonus()) base.emplace_back(MELDS_MJ::bonus, hand.back().encode()), hand.pop_back();
  if CEXP (enable_kong) assert(cards <= hand.size() && hand.size() <= cards + 4);
  else assert(hand.size() == cards);
  arr<u8, 45> counter{};
  for (auto CR card : hand) ++counter[card.encode()];
  u32 sum_counter = std::reduce(counter.begin(), counter.begin() + 34, 0_u32);
  auto CR counter_bk = counter;
  if CEXP (enable_13terminal)
    if (hand.size() == cards) {
      record_t waiting, prepared = base;
      auto f = [&](u32 eye = -1_u32) {
        std::list<guard> gs;
        for (auto c : vecu{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33})
          if (auto cnt = counter[c]; c != eye && cnt) gs.emplace_back(prepared, counter, sum_counter, c, MELDS_MJ::orphan);
        if (sum_counter)
          flt_ (u32, c, 0, 34)
            if (counter[c])
              flt_ (u32, i, 0, counter[c]) gs.emplace_back(waiting, counter, sum_counter, c, MELDS_MJ::orphan);
        ans.emplace_back(max_card_per_kind, terminal13, waiting, prepared);
      };
      bool _ = false;
      for (auto c : vecu{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33})
        if (auto cnt = counter[c]; cnt > 1) {
          guard g(prepared, counter, sum_counter, c, MELDS_MJ::pair);
          _ = true, f(c);
        }
      if (!_) f();
    }
  if CEXP (enable_7pairs)
    if (hand.size() == cards) {
      record_t waiting, prepared = base;
      flt_ (u32, i, 0, 34)
        if (counter[i]) {
          flt_ (u32, j, 0, counter[i] / 2) prepared.emplace_back(MELDS_MJ::pair, i);
          if (counter[i] & 1) waiting.emplace_back(MELDS_MJ::orphan, i);
        }
      ans.emplace_back(max_card_per_kind, pairs7, waiting, prepared);
    }

  auto proceed_no_kong = [&]() NE {
    record_t waiting, prepared = base;
    auto f = [&](auto&& f) NE {
      if (!sum_counter) {
        ans.emplace_back(max_card_per_kind, normal, waiting, prepared);
        return;
      }
      bool found = false;
      flt_ (u32, c, 0, 34) {
        u32 cnt = counter[c];
        if (!cnt) continue;
        if (cnt >= 3) {
          guard g_pung(prepared, counter, sum_counter, c, MELDS_MJ::pung);
          found = true, f(f);
        }
        if (!mahjong_card::is_honor(c) && c % 9 < 7 && counter[c + 1] && counter[c + 2]) {
          guard g_chow(prepared, counter, sum_counter, c, MELDS_MJ::chow);
          found = true, f(f);
        }
      }
      if (found) return;
      found = false;
      flt_ (u32, c, 0, 34) {
        u32 cnt = counter[c];
        if (!cnt) continue;
        if (cnt >= 2) {
          guard g_pair(waiting, counter, sum_counter, c, counter_bk[c] < max_card_per_kind ? MELDS_MJ::pair : MELDS_MJ::pair0);
          found = true, f(f);
        }
        if (!mahjong_card::is_honor(c)) {
          if (c % 9 != 8 && counter[c + 1]) {
            if (!(c % 9) && counter_bk[c + 2] < max_card_per_kind) {
              guard g_mian(waiting, counter, sum_counter, c, MELDS_MJ::bianr);
              found = true, f(f);
            } else if (c % 9 == 7 && counter_bk[c - 1] < max_card_per_kind) {
              guard g_mian(waiting, counter, sum_counter, c, MELDS_MJ::bianl);
              found = true, f(f);
            } else if (c % 9 && c % 9 < 7) {
              if (counter_bk[c - 1] < max_card_per_kind && counter_bk[c + 2] < max_card_per_kind) {
                guard g_mian(waiting, counter, sum_counter, c, MELDS_MJ::mian);
                found = true, f(f);
              } else if (counter_bk[c - 1] < max_card_per_kind) {
                guard g_mian(waiting, counter, sum_counter, c, MELDS_MJ::bianl);
                found = true, f(f);
              } else if (counter_bk[c + 2] < max_card_per_kind) {
                guard g_mian(waiting, counter, sum_counter, c, MELDS_MJ::bianr);
                found = true, f(f);
              }
            }
          }
          if (c % 9 < 7 && counter[c + 2] && counter_bk[c + 1] < max_card_per_kind) {
            guard g_kan(waiting, counter, sum_counter, c, MELDS_MJ::kan);
            found = true, f(f);
          }
        }
      }
      if (found) return;
      std::list<guard> g_orphans;
      flt_ (u32, c, 0, 34)
        if (counter[c]) g_orphans.emplace_back(waiting, counter, sum_counter, c, MELDS_MJ::orphan);
      f(f);
    };
    bool _ = false;
    flt_ (u32, c, 0, 34)
      if (counter[c] >= 2) {
        guard g_eye(waiting, counter, sum_counter, c, counter_bk[c] < max_card_per_kind ? MELDS_MJ::pair : MELDS_MJ::pair0);
        f(f);
      }
    if (!_) f(f);
  };

  if CEXP (enable_kong) {
    u32 kong_tot = (u32)hand.size() - cards;
    vecu kongs;
    flt_ (u32, i, 0, 34)
      if (counter[i] >= 4)
        flt_ (u32, j, 0, counter[i] / 4) kongs.push_back(i);
    assert(kong_tot <= kongs.size() && kongs.size() <= 4);
    sort(kongs);
    do {
      std::list<guard> guards;
      flt_ (u32, i, 0, kong_tot) guards.emplace_back(base, counter, sum_counter, kongs[i], MELDS_MJ::kong);
      proceed_no_kong();
    } while (std::next_permutation(kongs.begin(), kongs.end()));
  } else proceed_no_kong();
  for (auto& [_, __, waiting, prepared] : ans) sort(waiting), sort(prepared);
  return uniq(ans);
}

}  // namespace tifa_libs::game

#endif