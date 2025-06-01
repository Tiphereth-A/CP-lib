#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/opt/dlx.hpp"

#include "../base.hpp"

using namespace tifa_libs;
namespace PieceOperation {
constexpr u32 flip4(u32 x) { return (x & 1) << 3 | ((x >> 1) & 1) << 2 | ((x >> 2) & 1) << 1 | ((x >> 3) & 1); }
constexpr u32 expand4(u32 x) { return (x & 8) << 9 | (x & 4) << 6 | (x & 2) << 3 | (x & 1); }
constexpr u32 flip16(u32 x) { return flip4((x >> 12) & 15) << 12 | flip4((x >> 8) & 15) << 8 | flip4((x >> 4) & 15) << 4 | flip4(x & 15); }
constexpr u32 rot16(u32 x) { return expand4(flip4((x >> 12) & 15)) << 3 | expand4(flip4((x >> 8) & 15)) << 2 | expand4(flip4((x >> 4) & 15)) << 1 | expand4(flip4(x & 15)); }
constexpr u32 rearrange16(u32 x) {
  assert(x);
  while (!(x & 0xf000)) x <<= 4;
  while (!(x & 0x8888)) x = (((x >> 12) & 7) << 13) | (((x >> 8) & 7) << 9) | (((x >> 4) & 7) << 5) | ((x & 7) << 1);
  return x;
}

const u32 pieces_base[] = {0x1c800, 0x2f000, 0x3e800, 0x4cc00, 0x588e0, 0x6f400, 0x7ea00, 0x8ec00, 0x9e300, 0xa4e40, 0xb8c60, 0xcf800};
constexpr u32 flip(u32 piece) { return (piece & 0xf0000) | rearrange16(flip16(piece & 0xffff)); }
constexpr u32 rotate(u32 piece) { return (piece & 0xf0000) | rearrange16(rot16(piece & 0xffff)); }

std::vector<u32> getall() {
  std::set<u32> s;
  for (auto &&i : pieces_base) s.merge(std::set<u32>{i, rotate(i), rotate(rotate(i)), rotate(rotate(rotate(i))), flip(i), rotate(flip(i)), rotate(rotate(flip(i))), rotate(rotate(rotate(flip(i))))});
  std::vector<u32> ans;
  for (auto &&j : s) ans.push_back(j);
  return ans;
}
}  // namespace PieceOperation

const u32 pieces[60] = {0x14c00, 0x18c00, 0x1c400, 0x1c800, 0x28888, 0x2f000, 0x32e00, 0x344c0, 0x388c0, 0x38e00, 0x3c440, 0x3c880, 0x3e200, 0x3e800, 0x4cc00, 0x522e0, 0x588e0, 0x5e220, 0x5e880, 0x62f00, 0x644c4, 0x64c44, 0x64f00, 0x688c8, 0x68c88, 0x6f200, 0x6f400, 0x7ae00, 0x7c4c0, 0x7c8c0, 0x7ea00, 0x84cc0, 0x86e00, 0x88cc0, 0x8cc40, 0x8cc80, 0x8ce00, 0x8e600, 0x8ec00, 0x93e00, 0x944c8, 0x94c88, 0x97c00, 0x988c4, 0x98c44, 0x9c700, 0x9e300, 0xa4e40, 0xb26c0, 0xb6c80, 0xb8c60, 0xbc620, 0xc1f00, 0xc444c, 0xc888c, 0xc8f00, 0xcc444, 0xcc888, 0xcf100, 0xcf800};

class Board {
 protected:
  u64 data[10] = {};
  bool pplaced[16] = {};
  u32 pcord[16][2] = {{10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}, {10, 10}};

 public:
  constexpr Board() = default;

  friend auto &operator>>(istream_c auto &is, Board &board) {
    strn s;
    for (u64 _ = 0xfffffffff, i = 0; i < 10; ++i, _ >>= 4) {
      is >> s;
      board.data[i] = _;
      for (usz j = 0; j <= i; ++j)
        if (isalpha(s[j])) {
          board.pplaced[s[j] & 15] = true;
          auto &coord = board.pcord[s[j] & 15];
          coord[0] = std::min(coord[0], (u32)i);
          coord[1] = std::min(coord[1], (u32)j);
          board.data[i] |= u64(s[j] & 15) << (4 * (9 - j));
        }
    }
    return is;
  }

  friend auto &operator<<(ostream_c auto &os, Board const &board) {
    u32 _;
    for (usz i = 0; i < 10; ++i) {
      for (usz j = 0; j <= i; ++j) os << ((_ = board.get(i, j)) ? (char)(_ + '@') : '.');
      os << '\n';
    }
    return os;
  }

  constexpr u32 get(usz row, usz col) const {
    assert(row < 10 && col <= row);
    return (data[row] >> (4 * (9 - col))) & 15;
  }

  constexpr bool can_place_4x4(usz row, usz col, usz piece) const {
    if (row > 9 || col > row) return false;
    auto &&pid = (piece >> 16) & 15;
    if (pplaced[pid]) {
      if (row != pcord[pid][0] || col != pcord[pid][1])
        return false;
    } else
      pid = 0;

    usz p[4] = {(piece >> 12) & 15, (piece >> 8) & 15, (piece >> 4) & 15, piece & 15};

    for (usz i = 0, s = 0, end_ = !!p[0] + !!p[1] + !!p[2] + !!p[3]; i < end_; ++i) {
      if (row + i > 9) return false;
      isz ofs = 4 * (6 - (isz)col);
      s = (ofs < 0 ? (data[row + i] << -ofs | ((1ull << -ofs) - 1)) : (data[row + i] >> ofs)) & 0xffff;
      s = usz(((s >> 12) & 15) == pid) << 3 | usz(((s >> 8) & 15) == pid) << 2 | usz(((s >> 4) & 15) == pid) << 1 | ((s & 15) == pid);
      if (p[i] & (p[i] ^ s)) return false;
    }
    return true;
  }

  constexpr void place_4x4(usz row, usz col, usz piece) {
    auto &&pid = (piece >> 16) & 15;
    for (usz i = row; i < std::min((usz)10, row + 4); ++i)
      for (usz j = col; j < std::min((usz)10, col + 4); ++j) data[i] |= ((pid * !!(piece & (1 << (15 - (i - row) * 4 - j + col)))) << (4 * (9 - j)));
  }
};

strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  Board board;
  fin >> board;
  vvecb maps;
  vec<pt3<usz>> coord;
  {
    auto encode = [](usz row, usz col) { return 12 + row * (row + 1) / 2 + col; };
    vecb _;
    for (usz id = 0; id < sizeof(pieces) / sizeof(pieces[0]); ++id)
      for (usz i = 0; i < 10; ++i)
        for (usz j = 0; j <= i; ++j)
          if (board.can_place_4x4(i, j, pieces[id])) {
            _.clear();
            _.resize(67);
            _[((pieces[id] >> 16) & 15) - 1] = 1;
            for (usz _i = 0; _i < 4; ++_i)
              for (usz _j = 0; _j < 4; ++_j) _[encode(i + _i, j + _j)] = pieces[id] & (1 << (15 - _i * 4 - _j));
            coord.emplace_back(id, i, j);
            maps.push_back(_);
          }
  }

  auto res = opt::DLX(maps).dance(fn_0);
  if (!res.has_value()) {
    ss << "No solution";
    goto end__;
  }
  for (auto x : res.value()) {
    auto &&[id, i, j] = coord[x - 1];
    board.place_4x4(i, j, pieces[id]);
  }
  ss << board;

end__:
  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1501", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want, _;
    while (std::getline(fans, _)) want += _ + '\n';
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: test("3"); break;
    case unittest::ts_random_01: test("4"); break;
    case unittest::ts_random_02: test("5"); break;
    case unittest::ts_random_03: test("6"); break;
    case unittest::ts_random_04: test("7"); break;
    case unittest::ts_random_05: test("8"); break;
    case unittest::ts_random_06: test("9"); break;
    case unittest::ts_random_07: test("10"); break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}