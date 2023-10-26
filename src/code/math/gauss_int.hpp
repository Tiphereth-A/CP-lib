#ifndef TIFA_LIBS_MATH_GAUSS_INT
#define TIFA_LIBS_MATH_GAUSS_INT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint, i64 M>
class GaussInt {
 private:
  mint r_, i_;

 public:
  constexpr GaussInt(mint const &real = mint(), mint const &imag = mint()) : r_(real), i_(imag) {}
  constexpr mint real() const { return r_; }
  constexpr mint imag() const { return i_; }
  constexpr void real(mint x) { r_ = x; }
  constexpr void imag(mint x) { i_ = x; }
  constexpr GaussInt &operator*=(mint const &x) {
    r_ *= x;
    i_ *= x;
    return *this;
  }
  constexpr GaussInt &operator/=(mint const &x) {
    r_ /= x;
    i_ /= x;
    return *this;
  }
  constexpr GaussInt &operator+=(GaussInt const &x) {
    r_ += x.real();
    i_ += x.imag();
    return *this;
  }
  constexpr GaussInt &operator-=(GaussInt const &x) {
    r_ -= x.real();
    i_ -= x.imag();
    return *this;
  }
  constexpr GaussInt &operator*=(GaussInt const &x) {
    const mint _ = r_ * x.real() + i_ * x.imag() * M;
    i_ = r_ * x.imag() + i_ * x.real();
    r_ = _;
    return *this;
  }
  constexpr GaussInt &operator/=(GaussInt const &x) {
    const mint _ = r_ * x.real() - i_ * x.imag() * M;
    const mint n_ = x.norm();
    i_ = (i_ * x.real() - r_ * x.imag()) / n_;
    r_ = _ / n_;
    return *this;
  }
  constexpr friend GaussInt operator*(GaussInt x, mint const &y) { return x *= y; }
  constexpr friend GaussInt operator/(GaussInt x, mint const &y) { return x /= y; }
  constexpr friend GaussInt operator+(GaussInt x, GaussInt const &y) { return x += y; }
  constexpr friend GaussInt operator-(GaussInt x, GaussInt const &y) { return x -= y; }
  constexpr friend GaussInt operator*(GaussInt x, GaussInt const &y) { return x *= y; }
  constexpr friend GaussInt operator/(GaussInt x, GaussInt const &y) { return x /= y; }
  constexpr friend GaussInt conj(GaussInt const &x) { return GaussInt{x.r_, -x.i_}; }
  constexpr friend mint norm(GaussInt const &x) { return x.r_ * x.r_ + x.i_ * x.i_ * M; }

  constexpr friend bool operator==(GaussInt const &x, GaussInt const &y) { return x.real() == y.real() && x.imag() == y.imag(); }
  constexpr friend bool operator!=(GaussInt const &x, GaussInt const &y) { return !(x == y); }

  friend std::istream &operator>>(std::istream &is, GaussInt &x) { return is >> x.r_ >> x.i_; }
  friend std::ostream &operator<<(std::ostream &os, GaussInt const &x) { return os << '(' << x.real() << ',' << x.imag() << ')'; }
};
template <class mint>
class GaussInt<mint, -1> : public std::complex<mint> {
 public:
  constexpr GaussInt(std::complex<mint> const &&c) : std::complex<mint>(c) {}
  constexpr GaussInt(mint const &real = mint(), mint const &imag = mint()) : std::complex<mint>(real, imag) {}

  operator std::complex<mint>() { return *this; }
};

}  // namespace tifa_libs::math

#endif