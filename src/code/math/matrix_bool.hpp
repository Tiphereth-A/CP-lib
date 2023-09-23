#ifndef TIFA_LIBS_MATH_MATRIX_BOOL
#define TIFA_LIBS_MATH_MATRIX_BOOL

#include "../util/util.hpp"

#include "matrix.hpp"

namespace tifa_libs::math {

class matrix_bool: public matrix<bool> {
  using self = matrix_bool;
  using base = matrix<bool>;

  constexpr static auto isz__ = [](bool x) { return !x; };

public:
  matrix_bool(size_t row, size_t col, bool val = false):
    base(row, col, isz__, val) {}
  matrix_bool(size_t row, size_t col, const std::valarray<bool> &data_):
    base(row, col, isz__, data_) {}
  i64 do_gauss_range(size_t row_start, size_t row_end, bool clear_all = true) override {
    assert(row_start < row_end && row_end <= this->row_size());
    u64 rk = 0;
    bool neg = false;
    for (size_t i = row_start; i < std::min(row_end, this->col_size()); ++i) {
      if (!(*this)(rk, i)) {
        for (size_t j = rk + 1; j < row_end; ++j)
          if ((*this)(j, i)) {
            this->swap_row(j, rk);
            neg ^= true;
            break;
          }
        if (!(*this)(rk, i)) continue;
      }
      std::valarray<bool> tmp_ = data[std::slice(rk * this->col_size() + i + 1, this->col_size() - i - 1, 1)];
      for (u64 j = clear_all ? 0 : rk + 1; j < row_end; ++j) {
        if (j == rk || iszero((*this)(j, i))) continue;
        (*this)(j, i) = false;
        data[std::slice(j * this->col_size() + i + 1, this->col_size() - i - 1, 1)] ^= tmp_;
      }
      ++rk;
    }
    return neg ? -((i64)rk) : (i64)rk;
  }
  size_t rank() const = delete;
  bool det() const = delete;
};

}  // namespace tifa_libs::math

#endif