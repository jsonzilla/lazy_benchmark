#include <benchmark\benchmark.h>

#include <iostream>

#include "lazy_val.h"

#pragma optimize( "g", off )

long double factorial(long double n)
{
  return (n == 1.0 || n == 0.0) ? 1.0 : factorial(n - 1.0) * n;
}

auto var = []() {
  return factorial(132);
};

auto val = lazy{
  return var();
};

static void Standard(benchmark::State& state) {
    if (state.thread_index == 0) {}
    while (state.KeepRunning()) {
      auto x = var() + 1.0;
    }
    if (state.thread_index == 0) {}
}

static void StandardLazy(benchmark::State& state) {
  if (state.thread_index == 0) {}
  while (state.KeepRunning()) {
    auto x = val + 1.0;
  }
  if (state.thread_index == 0) {}
}

BENCHMARK(Standard)->Repetitions(2);
BENCHMARK(StandardLazy)->Repetitions(2);
BENCHMARK_MAIN();