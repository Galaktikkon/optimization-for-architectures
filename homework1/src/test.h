using namespace std;

#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <time.h>

#define REPEATS 25

static double gtod_ref_time_sec = 0.0;

double dclock() {
  double the_time, norm_sec;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  if (gtod_ref_time_sec == 0.0)
    gtod_ref_time_sec = (double)tv.tv_sec;
  norm_sec = (double)tv.tv_sec - gtod_ref_time_sec;
  the_time = norm_sec + tv.tv_usec * 1.0e-6;
  return the_time;
}

string formatSize(size_t bytes) {
  const char *sizes[] = {
      "B",
      "KB",
      "MB",
  };
  int order = 0;
  double size = bytes;

  while (size >= 1024 && order < 4) {
    size /= 1024;
    ++order;
  }

  ostringstream out;
  out << fixed << setprecision(2) << size << ' ' << sizes[order];
  return out.str();
}

double test(string (*func)(string &), string &input, bool verbose = false) {
  double start, end;
  string result, size = formatSize(input.size());

  start = dclock();
  for (int i = 0; i < REPEATS; i++) {
    result = func(input);
  }
  end = dclock();

  double bencharkTime = (end - start);

  if (verbose) {
    printf(
        "Benchmark result for input size %s over %d iterations: %.6f seconds\n",
        size.c_str(), REPEATS, bencharkTime);
  }

  return bencharkTime;
};