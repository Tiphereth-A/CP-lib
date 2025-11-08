#ifndef TIFALIBS_GAME_POKER_DATA
#define TIFALIBS_GAME_POKER_DATA

#include "../util/traits_others.hpp"

namespace tifa_libs::game {

struct poker_card {
  static CEXP strn valid_rank = "23456789TJQKA";
  static CEXP strn valid_suit = "SHDC";

  static CEXP u32 rank_value(char c) NE {
    auto ret = valid_rank.find(c);
    assert(ret != strn::npos);
    return (u32)ret + 2;
  }

  CEXP bool valid() CNE {
    retif_((rank < 1 || rank > 14), false);
    return valid_suit.find(suit) != strn::npos;
  }
  CEXP auto operator<=>(poker_card r) CNE {
    if (suit == r.suit) return rank <=> r.rank;
    return valid_suit.find(suit) <=> valid_rank.find(r.suit);
  }
  friend CEXP bool operator==(poker_card l, poker_card r) NE { return std::is_eq(l <=> r); }
  friend auto& operator>>(tifa_libs::istream_c auto& is, poker_card& p) NE {
    char c;
    (is >> c >> p.suit), p.rank = rank_value(c), p.suit = toupper(p.suit);
    return is;
  }

  u32 rank;
  char suit;
};

}  // namespace tifa_libs::game

#endif