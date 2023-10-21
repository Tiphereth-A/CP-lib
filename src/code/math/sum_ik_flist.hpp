#ifndef TIFA_LIBS_MATH_SUM_IK_FUNC
#define TIFA_LIBS_MATH_SUM_IK_FUNC

namespace tifa_libs::math {

template <class T>
constexpr T sum_i0(T n) { return n; }
template <class T>
constexpr T sum_i1(T n) { return n * (n + 1) / 2; }
template <class T>
constexpr T sum_i2(T n) { return sum_i1(n) * (n * 2 + 1) / 3; }
template <class T>
constexpr T sum_i3(T n) {
  auto _ = sum_i1(n);
  return _ * _;
}
template <class T>
constexpr T sum_i4(T n) { return sum_i2(n) * (sum_i1(n) * 6 - 1) / 5; }
template <class T>
constexpr T sum_i5(T n) { return sum_i3(n) * (sum_i1(n) * 4 - 1) / 3; }
template <class T>
constexpr T sum_i6(T n) { return (sum_i2(n) * sum_i1(n) * 12 - sum_i4(n) * 5) / 7; }
template <class T>
constexpr T sum_i7(T n) {
  auto _ = sum_i3(n);
  return _ * _ * 2 - sum_i5(n);
}

template <class T>
constexpr T (*sum_ik[])(T) = {sum_i0<T>, sum_i1<T>, sum_i2<T>, sum_i3<T>, sum_i4<T>, sum_i5<T>, sum_i6<T>, sum_i7<T>};

}  // namespace tifa_libs::math

#endif