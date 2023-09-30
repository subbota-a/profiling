// Substring sort
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <thread>

#include "compare.h"
#include <benchmark/benchmark.h>

using std::cout;
using std::endl;
using std::minstd_rand;
using std::unique_ptr;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

struct DataSet {
  DataSet(unsigned int L, unsigned int N)
      : s(std::unique_ptr<char[]>(new char[L])), vs(N) {}

  unique_ptr<char[]> s;
  vector<const char *> vs;
};

DataSet Prepare(unsigned int L, unsigned int N) {
  DataSet ds(L, N);

  {
    minstd_rand rgen;
    using rand_t = minstd_rand::result_type;
    if (0)
      for (char *p = ds.s.get(), *end = p + L; p != end;
           p += sizeof(rand_t)) { // Option A
        const rand_t x = rgen();
        ::memcpy(p, &x, sizeof(x));
      }
    else if (0)
      for (unsigned int i = 0; i < L; ++i) { // Option B
        ds.s[i] = 'a' + (rgen() % ('z' - 'a' + 1));
      }
    else { // Option C
      ::memset(ds.s.get(), 'a', L * sizeof(char));
      for (unsigned int i = 0; i < L / 1024; ++i) {
        ds.s[rgen() % (L - 1)] = 'a' + (rgen() % ('z' - 'a' + 1));
      }
    }
    ds.s[L - 1] = 0;
    for (unsigned int i = 0; i < N; ++i) {
      ds.vs[i] = &ds.s[rgen() % (L - 1)];
    }
    // cout << "s=" << s.get() << endl;
    // for (unsigned int i = 0; i < N; ++i) cout << "vs[" << i << "]=" << vs[i]
    // << endl;
  }
  // cout << "Prep time(L=" << L << ", N=" << N << "): " <<
  // duration_cast<milliseconds>(t1 - t0).count() << "ms" << endl;
  return ds;
}

void BM_compare1(benchmark::State &state) {
  auto ds = Prepare(state.range(0), state.range(1));
  int counter = 0;
  for (auto _ : state) {
    state.ResumeTiming();
    std::sort(ds.vs.begin(), ds.vs.end(), [&](const char *a, const char *b) {
      ++counter;
      return compare1(a, b, state.range(0));
    });
    state.PauseTiming();
    ds = Prepare(state.range(0), state.range(1));
  }
  benchmark::DoNotOptimize(counter);
}

void BM_compare2(benchmark::State &state) {
  auto ds = Prepare(state.range(0), state.range(1));
  int counter = 0;
  for (auto _ : state) {
    state.ResumeTiming();
    std::sort(ds.vs.begin(), ds.vs.end(), [&](const char *a, const char *b) {
      ++counter;
      return compare2(a, b);
    });
    state.PauseTiming();
    ds = Prepare(state.range(0), state.range(1));
  }
  benchmark::DoNotOptimize(counter);
}

BENCHMARK(BM_compare1)
    ->Args({1 << 18, 1 << 14})
    ->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK(BM_compare2)
    ->Args({1 << 18, 1 << 14})
    ->Unit(benchmark::TimeUnit::kMillisecond);

BENCHMARK_MAIN();

//int main()
//{
//  auto ds = Prepare(1 << 18, 1 << 14);
//  auto start = std::chrono::steady_clock::now();
//  std::sort(ds.vs.begin(), ds.vs.end(), compare2);
//  auto duration= std::chrono::steady_clock::now() - start;
//  std::cout << std::chrono::duration_cast< std::chrono::duration<double, std::milli>>(duration).count() << "ms\n";
//}
