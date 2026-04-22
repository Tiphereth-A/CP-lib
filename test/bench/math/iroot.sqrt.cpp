#include <benchmark/benchmark.h>

#include "../../../src/math/iroot/sqrt/lib.hpp"

using namespace tifa_libs;

volatile u32 x = 1'000'000'007;

static void BM_clib(benchmark::State& state) {
  for (auto _ : state) {
    auto res = (u32)sqrt(x);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(BM_clib);

static void BM_my(benchmark::State& state) {
  for (auto _ : state) {
    auto res = isqrt(x);
    benchmark::DoNotOptimize(res);
  }
}
BENCHMARK(BM_my);

BENCHMARK_MAIN();

/*comparison
BM_clib BM_my
*/
