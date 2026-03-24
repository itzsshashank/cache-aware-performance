# Cache-Aware Performance Analysis

**Language:** C++ | **Platform:** Linux/Windows | **Focus:** Microbenchmarking, Cache Efficiency  

This repository contains implementations and benchmarks for cache-aware matrix transpose algorithms to study memory access patterns and cache-line utilization. The project explores the impact of blocking strategies, data alignment, and layout on performance.

## Project Overview
- Implemented variants of matrix transpose optimized for cache usage
- Conducted microbenchmarks to measure execution time and cache efficiency
- Compared empirical performance against theoretical cache behavior to identify bottlenecks and analyze speedups/slowdowns

## Features
- **Multiple transpose implementations:**
  - Naive (no optimization)
  - Blocked/tiled with various block sizes (8x8, 16x16, 32x32, 64x64)
  - Cache-oblivious recursive algorithm
- **Comprehensive benchmarking framework**
- **Verification of correctness** for all implementations
- **Performance profiling** using standard Linux tools (perf)
- **Easy-to-use scripts** for reproducing benchmarks

## Implementations

### 1. Naive Transpose
Simple row-to-column copy with no cache optimization. Poor spatial locality on writes leads to high cache miss rates.

```cpp
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
        B[j][i] = A[i][j];  // Strided writes
```

### 2. Blocked Transpose
Divides the matrix into fixed-size blocks that fit in cache. Improves temporal and spatial locality by processing each block completely before moving to the next.

**Block sizes tested:** 8×8, 16×16, 32×32, 64×64

### 3. Cache-Oblivious Transpose
Recursive divide-and-conquer algorithm that automatically adapts to any cache hierarchy without tuning. No hardcoded block sizes - works optimally across different systems.

## Building and Running

### Linux

#### Quick Start
```bash
# Build and run
make
make run

# Run with cache profiling
make perf

# Or use the automated script
chmod +x run_benchmark.sh
./run_benchmark.sh
```

#### Manual Build
```bash
g++ -std=c++11 -O3 -Wall -Wextra main.cpp naive_transpose.cpp \
    blocked_transpose.cpp cache_oblivious_transpose.cpp \
    -o build/transpose_benchmark

./build/transpose_benchmark
```

### Windows

#### PowerShell Script (Recommended)
```powershell
.\run_benchmark.ps1
```

#### Manual Build (MinGW)
```cmd
g++ -std=c++11 -O3 -Wall -Wextra main.cpp naive_transpose.cpp blocked_transpose.cpp cache_oblivious_transpose.cpp -o build\transpose_benchmark.exe

.\build\transpose_benchmark.exe
```

#### Manual Build (MSVC)
```cmd
cl /EHsc /O2 /Fe:build\transpose_benchmark.exe main.cpp naive_transpose.cpp blocked_transpose.cpp cache_oblivious_transpose.cpp

.\build\transpose_benchmark.exe
```

## Benchmark Output

The benchmark produces output similar to:

```
=================================================
  Cache-Aware Matrix Transpose Benchmark
=================================================
Matrix Size: 2048 x 2048
Element Size: 8 bytes
Total Matrix Size: 32.00 MB
Cache Line Size: 64 bytes (8 doubles)
=================================================

Running benchmarks...

Testing naive transpose... OK
Testing blocked transpose (8x8)... OK
Testing blocked transpose (16x16)... OK
Testing blocked transpose (32x32)... OK
Testing blocked transpose (64x64)... OK
Testing cache-oblivious transpose... OK

=================================================
  Benchmark Results
=================================================
Algorithm             Time (ms)     Speedup
-------------------------------------------------
Naive                    245.32        1.00x
Blocked 8x8              156.78        1.56x
Blocked 16x16            142.45        1.72x
Blocked 32x32            138.92        1.77x
Blocked 64x64            145.23        1.69x
Cache Oblivious          140.11        1.75x
=================================================
```

## Performance Analysis

### Expected Results

**Key Observations:**
- **Naive transpose** suffers from poor cache performance due to strided writes
- **Blocked implementations** show significant speedups (1.5-2x typical)
- **Optimal block size** depends on cache sizes (typically 16-32 for L1)
- **Cache-oblivious** performs well without tuning
- Larger matrices amplify cache effects

### Cache Hierarchy Impact

With the following cache configuration (see [NOTES.md](NOTES.md)):
- L1: ~1.2 MB
- L2: ~11.5 MB
- L3: ~24.0 MB
- Cache line: 64 bytes (8 doubles)

**Matrix size: 2048×2048 doubles = 32 MB**

The matrix exceeds L1 and L2 caches, making cache-aware algorithms essential for performance.

## Profiling with Linux Perf

### Basic Cache Statistics
```bash
perf stat -e cache-references,cache-misses,cycles,instructions \
    ./build/transpose_benchmark
```

### Detailed Cache Profiling
```bash
perf stat -e L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses \
    ./build/transpose_benchmark
```

### Expected Metrics
- **Naive:** High L1 miss rate (>50%), poor cache efficiency
- **Blocked:** Lower miss rate (~20-30%), better bandwidth utilization
- **Cache-oblivious:** Similar to best blocked variant

## Project Structure

```
cache-aware-performance/
├── main.cpp                         # Benchmarking framework
├── naive_transpose.cpp              # Naive implementation
├── blocked_transpose.cpp            # Blocked variants (8/16/32/64)
├── cache_oblivious_transpose.cpp    # Recursive cache-oblivious
├── Makefile                         # Build configuration
├── run_benchmark.sh                 # Linux benchmark script
├── run_benchmark.ps1                # Windows benchmark script
├── NOTES.md                         # Cache analysis notes
├── README.md                        # This file
└── build/                           # Build output directory
```

## Key Concepts

### Cache Blocking (Tiling)
Divides computation into blocks that fit in cache, improving:
- **Temporal locality:** Reuse data while in cache
- **Spatial locality:** Access consecutive memory
- **Cache line utilization:** Better use of fetched data

### Cache-Oblivious Algorithms
Recursive algorithms that work optimally at all levels of the cache hierarchy without knowing cache sizes. Automatically adapts to different systems.

### Memory Access Patterns
- **Sequential:** Good spatial locality, hardware prefetching
- **Strided:** Poor locality, frequent cache misses
- **Blocked:** Balanced locality at all cache levels


## References

- **Cache-Oblivious Algorithms:** Frigo et al., "Cache-Oblivious Algorithms"
- **Loop Tiling:** Wolfe, "High Performance Compilers for Parallel Computing"
- **Cache Performance:** Hennessy & Patterson, "Computer Architecture: A Quantitative Approach"

