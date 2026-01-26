# Cache-Aware Performance Analysis

**Language:** C++ | **Platform:** Linux | **Focus:** Microbenchmarking, Cache Efficiency  

This repository contains implementations and benchmarks for cache-aware matrix transpose algorithms to study memory access patterns and cache-line utilization. The project explores the impact of blocking strategies, data alignment, and layout on performance.

## Project Overview
- Implemented variants of matrix transpose optimized for cache usage.
- Conducted microbenchmarks to measure execution time and cache efficiency.
- Compared empirical performance against theoretical cache behavior to identify bottlenecks and analyze speedups/slowdowns.

## Features
- Cache-aware matrix transpose algorithms
- Support for different block sizes and data layouts
- Performance profiling using standard Linux tools (perf, gprof, etc.)
- Scripts for reproducing benchmarks
