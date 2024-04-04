#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 1000000007;

#define GENTCs_3nttu64
#define GENTCs_3ntts
#define GENTCs_3nttd0
#define GENTCs_mtts
#define GENTCs_mttd0

int main() {
#define GENTCs_3nttd1
#define GENTCs_mttd1
  u32 n, m;
  tifa_libs::fin >> n >> m;
#ifdef GENTC_3nttu64_s30
  vecu64 a(n), b(m);
#endif
#ifdef GENTC_3nttu64_ss
  vecu64 a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_s30
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_s63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_ss
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_s30
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_s63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_ss
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_d31
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_d63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_s30_ds
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_d31
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_d63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_3ntt_ss_ds
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_s30
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_s63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_ss
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_d31
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_d63
  vec<mint> a(n), b(m);
#endif
#ifdef GENTC_mtt_ds
  vec<mint> a(n), b(m);
#endif
  tifa_libs::fin >> a >> b;
#ifdef GENTC_3nttu64_s30
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt_u64(ntt3, a, b, MOD) << '\n';
#endif
#ifdef GENTC_3nttu64_ss
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt_u64(ntt3, a, b, MOD) << '\n';
#endif
#ifdef GENTC_3ntt_s30_s30
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_s30_s63
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_s30_ss
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_s30
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_s63
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_ss
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_s30_d31
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_s30_d63
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_s30_ds
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_d31
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_d63
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_3ntt_ss_ds
  ntt3_t ntt3;
  tifa_libs::fout << tifa_libs::math::conv_3ntt(ntt3, a, b) << '\n';
#endif
#ifdef GENTC_mtt_s30
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
#ifdef GENTC_mtt_s63
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
#ifdef GENTC_mtt_ss
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
#ifdef GENTC_mtt_d31
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
#ifdef GENTC_mtt_d63
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
#ifdef GENTC_mtt_ds
  tifa_libs::math::FFT<long double> fft;
  tifa_libs::fout << tifa_libs::math::conv_mtt(fft, a, b) << '\n';
#endif
  return 0;
}
