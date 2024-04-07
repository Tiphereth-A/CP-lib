#ifndef TIFALIBS_GAME_TEXAS_HOLDEM
#define TIFALIBS_GAME_TEXAS_HOLDEM

#include "../bit/cntlsb.hpp"
#include "../util/util.hpp"

namespace tifa_libs::game {
namespace texas_holdem_impl_ {
constexpr int bsr(int x) { return 30 - bit::cntlsb(x); }
// Returns the submask containing highest k bits set
// Returns -1 instead if std::popcount(a) < k
constexpr int hbits(int a, int k) {
  int b = 0;
  for (int i = 0; i < k; ++i) {
    if (!a) return -1;
    a &= ~(b |= 1 << bsr(a));
  }
  return b;
}

class th_card {
 protected:
  int data = 0;

 public:
  static constexpr char RANKS[16] = "0123456789TJQKA";
  static constexpr char SUITS[5] = "CDHS";
  explicit constexpr th_card() {}
  constexpr th_card(char rank, char suit) { encode(rank, suit); }
  explicit constexpr th_card(strnv str) : th_card(str[0], str[1]) { assert(str.size() == 2); }
  // Parses a card in a format as "2C"
  // @return: 4 * (rank - 2) + suit  (2 <= rank <= 14)
  constexpr void encode(char rank, char suit) {
    int r = 2, s = 0;
    for (; r < 15; ++r)
      if (RANKS[r] == rank) break;
    assert(r < 15);
    for (; s < 4; ++s)
      if (SUITS[s] == suit) break;
    assert(s < 4);
    data = (r - 2) << 2 | s;
  }
  constexpr int get_rank() const { return (data >> 2) + 2; }
  constexpr int get_suit() const { return data & 3; }
  // @return: {rank_char, suit_char}
  constexpr ptt<char> decode() const { return {RANKS[get_rank()], SUITS[get_suit()]}; }
  friend std::istream &operator>>(std::istream &is, th_card &card) {
    char rk, st;
    is >> rk >> st;
    card.encode(rk, st);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, th_card const &card) {
    auto &&_ = card.decode();
    return os << _.first << _.second;
  }
};

enum th_category {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH
};

class th_hand {
  vec<th_card> cds;
  // ranks for all
  int rka = 0;
  // suit -> rank
  int mps[4] = {};
  // rank -> count
  int cnt[15] = {};
  // count -> rank
  int mpc[5] = {};

 public:
  explicit constexpr th_hand() : cds(5) {}
  // Set first 5 element as hand
  constexpr void reset(vec<th_card> const &cards) {
    assert(cards.size() >= 5);
    std::copy(cards.begin(), cards.begin() + 5, cds.begin());
    for (auto &&card : cds) {
      auto r = card.get_rank(), s = card.get_suit();
      rka |= mps[s] |= 1 << r;
      ++cnt[r];
    }
    for (int r = 2; r < 15; ++r) mpc[cnt[r]] |= 1 << r;
  }
  // Returns the best poker hand with the tie-breaker in [0, 2^20)
  constexpr std::pair<th_category, int> parse() const {
    assert(cds.size() == 5);
    for (auto &&func : checks)
      if (auto [valid, cat, ans] = func(*this); valid) return {cat, ans};
    exit(1);
  }

  constexpr th_card &operator[](u32 x) { return cds[x]; }
  constexpr th_card const &operator[](u32 x) const { return cds[x]; }

  friend std::istream &operator>>(std::istream &is, th_hand &hands) {
    for (u32 i = 0; i < 5; ++i) is >> hands.cds[i];
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, th_hand const &hands) {
    for (u32 i = 0; i < 4; ++i) os << hands.cds[i] << ' ';
    return os << hands.cds[4];
  }

 private:
  // 8. STRAIGHT_FLUSH: highest (5 for A2345)
  static constexpr std::tuple<bool, th_category, int> is_straight_flush(th_hand const &h) {
    int f = 0;
    for (int s = 0; s < 4; ++s) f |= h.mps[s] & h.mps[s] << 1 & h.mps[s] << 2 & h.mps[s] << 3 & (h.mps[s] << 4 | h.mps[s] >> 14 << 5);
    return {!!f, STRAIGHT_FLUSH, bsr(f)};
  }
  // 7. FOUR_OF_A_KIND: quadruple, other card
  static constexpr std::tuple<bool, th_category, int> is_four_of_a_kind(th_hand const &h) {
    if (!h.mpc[4]) return {false, FOUR_OF_A_KIND, 0};
    const int r4 = bsr(h.mpc[4]);
    return {true, FOUR_OF_A_KIND, r4 << 4 | bsr(h.rka ^ 1 << r4)};
  }
  // 6. FULL_HOUSE: triple, pair
  static constexpr std::tuple<bool, th_category, int> is_full_house(th_hand const &h) {
    if (!h.mpc[3]) return {false, FULL_HOUSE, 0};
    const int r3 = bsr(h.mpc[3]), d = (h.mpc[3] ^ 1 << r3) | h.mpc[2];
    if (!d) return {false, FULL_HOUSE, 1};
    const int r2 = bsr(d);
    return {true, FULL_HOUSE, r3 << 4 | r2};
  }
  // 5. FLUSH: 5 highest cards
  static constexpr std::tuple<bool, th_category, int> is_flush(th_hand const &h) {
    int flush = -1;
    for (int s = 0, _ = 0; s < 4; ++s)
      if (flush < (_ = hbits(h.mps[s], 5))) flush = _;
    return {flush >= 0, FLUSH, flush};
  }
  // 4. STRAIGHT: highest (5 for A2345)
  static constexpr std::tuple<bool, th_category, int> is_straight(th_hand const &h) {
    const int f = h.rka & h.rka << 1 & h.rka << 2 & h.rka << 3 & (h.rka << 4 | h.rka >> 14 << 5);
    return {!!f, STRAIGHT, bsr(f)};
  }
  // 3. THREE_OF_A_KIND: triple, 2 highest other cards
  static constexpr std::tuple<bool, th_category, int> is_three_of_a_kind(th_hand const &h) {
    if (!h.mpc[3]) return {false, THREE_OF_A_KIND, 0};
    const int r3 = bsr(h.mpc[3]);
    return {true, THREE_OF_A_KIND, r3 << 16 | hbits(h.rka ^ 1 << r3, 2)};
  }
  // 2. TWO_PAIR: larger pair, smaller pair, other card
  // 1. ONE_PAIR: pair, 3 highest other cards
  static constexpr std::tuple<bool, th_category, int> is_pair(th_hand const &h) {
    if (!h.mpc[2]) return {false, ONE_PAIR, 0};
    const int r2 = bsr(h.mpc[2]);
    const int d = h.mpc[2] ^ 1 << r2;
    if (!d) return {true, ONE_PAIR, r2 << 16 | hbits(h.rka ^ 1 << r2, 3)};
    const int r22 = bsr(d);
    return {true, TWO_PAIR, r2 << 8 | r22 << 4 | bsr(h.rka ^ 1 << r2 ^ 1 << r22)};
  }
  // 0. HIGH_CARD: 5 highest cards
  static constexpr std::tuple<bool, th_category, int> is_high_card(th_hand const &h) { return {true, HIGH_CARD, hbits(h.rka, 5)}; }
  //! The judger of all the categories
  static constexpr std::tuple<bool, th_category, int> (*checks[8])(th_hand const &) = {
      is_straight_flush,
      is_four_of_a_kind,
      is_full_house,
      is_flush,
      is_straight,
      is_three_of_a_kind,
      is_pair,
      is_high_card};
};
}  // namespace texas_holdem_impl_

using texas_holdem_impl_::th_category, texas_holdem_impl_::th_card, texas_holdem_impl_::th_hand;

}  // namespace tifa_libs::game

#endif