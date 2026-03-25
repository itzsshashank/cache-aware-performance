#!/bin/bash

# Cache-Aware Performance Benchmark Script
# Run comprehensive benchmarks with cache profiling

echo "=========================================="
echo "Cache-Aware Performance Benchmark Suite"
echo "=========================================="
echo ""

# Build the project
echo "Building project..."
make clean
make
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi
echo ""

# Check if perf is available
if command -v perf &> /dev/null; then
    PERF_AVAILABLE=true
    echo "Linux perf detected - will run cache profiling"
else
    PERF_AVAILABLE=false
    echo "Linux perf not available - running basic benchmarks only"
fi
echo ""

# Run basic benchmark
echo "=========================================="
echo "Running basic benchmark..."
echo "=========================================="
./build/transpose_benchmark
echo ""

# Run with cache statistics if perf is available
if [ "$PERF_AVAILABLE" = true ]; then
    echo "=========================================="
    echo "Running with cache statistics..."
    echo "=========================================="
    perf stat -e cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses,cycles,instructions ./build/transpose_benchmark 2>&1 | tee benchmark_results.txt
    echo ""
    echo "Results saved to benchmark_results.txt"
fi

echo ""
echo "Benchmark complete!"
