#include <benchmark/benchmark.h>

#include "../../../src/math/iroot/sqrt/lib.hpp"

using namespace tifa_libs;

volatile u32 x = 1'000'000'007;

static void BM_double(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize((u64)sqrt(pow(x, 1.5) / log(x)));
  }
}
BENCHMARK(BM_double);

static void BM_int(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(isqrt((u64)x * (isqrt(x) + 1) * 2 / ((u64)std::bit_width(x) * 3)));
  }
}
BENCHMARK(BM_int);

BENCHMARK_MAIN();
