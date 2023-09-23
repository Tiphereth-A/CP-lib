#ifndef TIFA_LIBS_MATH_MATRIX_INT
#define TIFA_LIBS_MATH_MATRIX_INT

#include "../util/util.hpp"

#include "matrix.hpp"

namespace tifa_libs::math {

template <class T>
class matrix_int: public matrix<T> {
  static_assert(std::is_integral<T>::value);
  using self = matrix_int<T>;
  using base = matrix<T>;

  constexpr static auto isz__ = [](T const &x) { return x == 0; };

public:
  matrix_int(size_t row, size_t col, const T &val = T{}):
    base(row, col, isz__, val) {}
  matrix_int(size_t row, size_t col, const std::valarray<T> &data_):
    base(row, col, isz__, data_) {}
  i64 do_gauss_range(size_t row_start, size_t row_end, bool clear_all = true) override {
    assert(row_start < row_end && row_end <= this->row_size());
    u64 rk = 0;
    bool neg = false;
    for (size_t i = row_start, now_row; i < std::min(row_end, this->col_size()); ++i) {
      neg ^= this->gauss_swapr__(now_row, rk, i, row_end);
      if (this->iszero((*this)(rk, i))) continue;
      for (u64 j = clear_all ? 0 : rk; j < row_end; ++j) {
        if (j == rk || this->iszero((*this)(j, i))) continue;
        while (true) {
          T _ = (*this)(j, i) / (*this)(rk, i);
          this->row(j) -= _ * this->row_varray(rk);
          if (!this->iszero((*this)(j, i))) {
            this->swap_row(rk, j);
            neg ^= 1;
          } else
            break;
        }
      }
      ++rk;
    }
    return neg ? -((i64)rk) : (i64)rk;
  }
  size_t rank() const = delete;
  T det() const = delete;
};

}  // namespace tifa_libs::math

#endif