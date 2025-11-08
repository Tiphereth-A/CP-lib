#ifndef TIFALIBS_GAME_MAHJONG_DATA
#define TIFALIBS_GAME_MAHJONG_DATA

#include "../util/traits_others.hpp"

namespace tifa_libs::game {

struct mahjong_card {
  static CEXP strn valid_rank = "123456789";
  static CEXP strn valid_suit = "MPSZB";

  static CEXP u32 rank_value(char c) NE {
    auto ret = valid_rank.find(c);
    assert(ret != strn::npos);
    return (u32)ret + 1;
  }

  static CEXP mahjong_card decode(u32 code) NE { return {code % 9 + 1, valid_suit[code / 9]}; }
  CEXP u32 encode() CNE { return (u32)valid_suit.find(suit) * 9 + rank - 1; }
  CEXP bool valid() CNE {
    retif_((rank < 1 || rank > 9), false);
    retif_((suit == 'Z' && rank > 7), false);
    retif_((suit == 'B' && rank > 8), false);
    return valid_suit.find(suit) != strn::npos;
  }

  static CEXP bool is_mixed_terminal(u32 code) NE { return code <= 33 && (27 <= code || code % 9 == 0 || code % 9 == 8); }
  static CEXP bool is_terminal(u32 code) NE { return code <= 26 && (code % 9 == 0 || code % 9 == 8); }
  static CEXP bool is_honor(u32 code) NE { return 27 <= code && code <= 33; }
  static CEXP bool is_wind(u32 code) NE { return 27 <= code && code <= 30; }
  static CEXP bool is_dragon(u32 code) NE { return 31 <= code && code <= 33; }
  static CEXP bool is_bonus(u32 code) NE { return 36 <= code && code <= 43; }
  static CEXP bool is_flower(u32 code) NE { return 36 <= code && code <= 39; }
  static CEXP bool is_season(u32 code) NE { return 40 <= code && code <= 43; }

  CEXP bool is_bonus() CNE { return suit == 'B'; }
  CEXP bool is_mixed_terminal() CNE { return suit != 'B' && (suit == 'Z' || rank == 1 || rank == 9); }
  CEXP bool is_terminal() CNE { return suit != 'Z' && is_mixed_terminal(); }
  CEXP bool is_honor() CNE { return suit == 'Z'; }
  CEXP bool is_wind() CNE { return suit == 'Z' && rank <= 4; }
  CEXP bool is_dragon() CNE { return suit == 'Z' && rank > 4; }
  CEXP bool is_flower() CNE { return suit == 'B' && rank <= 4; }
  CEXP bool is_season() CNE { return suit == 'B' && rank > 4; }

  friend CEXP auto operator<=>(mahjong_card l, mahjong_card r) NE {
    if (l.suit == r.suit) return l.rank <=> r.rank;
    return valid_suit.find(l.suit) <=> valid_rank.find(r.suit);
  }
  friend CEXP bool operator==(mahjong_card l, mahjong_card r) NE { return std::is_eq(l <=> r); }
  friend auto& operator>>(tifa_libs::istream_c auto& is, mahjong_card& p) NE {
    char c;
    (is >> c >> p.suit), p.rank = rank_value(c), p.suit = toupper(p.suit);
    return is;
  }

  u32 rank;
  char suit;
};
namespace literals {
CEXP mahjong_card operator""_mjm(unsigned long long x) NE { return {(u32)x, 'M'}; }
CEXP mahjong_card operator""_mjp(unsigned long long x) NE { return {(u32)x, 'P'}; }
CEXP mahjong_card operator""_mjs(unsigned long long x) NE { return {(u32)x, 'S'}; }
CEXP mahjong_card operator""_mjz(unsigned long long x) NE { return {(u32)x, 'Z'}; }
CEXP mahjong_card operator""_mjb(unsigned long long x) NE { return {(u32)x, 'B'}; }
}  // namespace literals

}  // namespace tifa_libs::game

#endif