#include <benchmark\benchmark.h>

#include <iostream>

#include "lazy_val.h"

#pragma optimize( "g", off )

double factorial(double n)
{
  return (n == 1.0 || n == 0.0) ? 1.0 : factorial(n - 1.0) * n;
}

static auto val = lazy{
  return factorial(22);
};

static auto var = [](){
  return factorial(22);
};

static void Standard(benchmark::State& state) {
    int number = 6;
    if (state.thread_index == 0) {
      number = 6;
    }
    while (state.KeepRunning()) {
      int i = 100;
      auto val = [number](){
        return number;
      };

      while (i > 0) {
        --i;
        number = i % 2;
      }
    }
    if (state.thread_index == 0) {
    
    }
}

static void StandardLazy(benchmark::State& state) {
  int number = 6;
  if (state.thread_index == 0) {
    number = 6;
  }
  while (state.KeepRunning()) {
      int i = 100;
      auto val = lazy{
        return number;
      };

      while (i > 0) {
        --i;
        number = i % 2;
      }    
  }
  if (state.thread_index == 0) {
    // Teardown
  }
}

BENCHMARK(Standard)->Repetitions(2);
BENCHMARK(StandardLazy)->Repetitions(2);
BENCHMARK_MAIN();