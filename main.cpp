#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int N = 2048;  // Matrix size

// Forward declarations
void transpose_naive(double A[N][N], double B[N][N]);
void transpose_blocked_8(double A[N][N], double B[N][N]);
void transpose_blocked_16(double A[N][N], double B[N][N]);
void transpose_blocked_32(double A[N][N], double B[N][N]);
void transpose_blocked_64(double A[N][N], double B[N][N]);
void transpose_cache_oblivious(double A[N][N], double B[N][N]);

// Timing function
template<typename Func>
double measure_time(Func f, double A[N][N], double B[N][N], int iterations = 5) {
    vector<double> times;
    
    for (int iter = 0; iter < iterations; iter++) {
        // Clear B matrix
        memset(B, 0, sizeof(double) * N * N);
        
        auto start = high_resolution_clock::now();
        f(A, B);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<microseconds>(end - start).count();
        times.push_back(duration / 1000.0);  // Converting to milliseconds
    }
    
    // Returning median time
    sort(times.begin(), times.end());
    return times[times.size() / 2];
}

// Verifying correctness
bool verify_transpose(double A[N][N], double B[N][N]) {
    for (int i = 0; i < min(100, N); i++) {
        for (int j = 0; j < min(100, N); j++) {
            if (abs(B[j][i] - A[i][j]) > 1e-9) {
                cout << "ERROR at (" << i << "," << j << "): " 
                     << B[j][i] << " != " << A[i][j] << endl;
                return false;
            }
        }
    }
    return true;
}


int main() {
    cout << "=================================================\n";
    cout << "  Cache-Aware Matrix Transpose Benchmark\n";
    cout << "=================================================\n";
    cout << "Matrix Size: " << N << " x " << N << endl;
    cout << "Element Size: " << sizeof(double) << " bytes\n";
    cout << "Total Matrix Size: " << (N * N * sizeof(double)) / (1024.0 * 1024.0) << " MB\n";
    cout << "Cache Line Size: 64 bytes (" << (64 / sizeof(double)) << " doubles)\n";
    cout << "=================================================\n\n";

    // Allocate matrices
    static double A[N][N];
    static double B[N][N];

    // Initialize matrix A with some pattern
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i * N + j;
        }
    }

    cout << "Running benchmarks...\n\n";
    
    // Benchmark each implementation
    struct BenchResult {
        string name;
        double time;
        double speedup;
    };
    
    vector<BenchResult> results;
    
    // Naive transpose
    cout << "Testing naive transpose..." << flush;
    double time_naive = measure_time(transpose_naive, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Naive", time_naive, 1.0});
    
    // Blocked transpose (8x8)
    cout << "Testing blocked transpose (8x8)..." << flush;
    double time_b8 = measure_time(transpose_blocked_8, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Blocked 8x8", time_b8, time_naive / time_b8});
    
    // Blocked transpose (16x16)
    cout << "Testing blocked transpose (16x16)..." << flush;
    double time_b16 = measure_time(transpose_blocked_16, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Blocked 16x16", time_b16, time_naive / time_b16});
    
    // Blocked transpose (32x32)
    cout << "Testing blocked transpose (32x32)..." << flush;
    double time_b32 = measure_time(transpose_blocked_32, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Blocked 32x32", time_b32, time_naive / time_b32});
    
    // Blocked transpose (64x64)
    cout << "Testing blocked transpose (64x64)..." << flush;
    double time_b64 = measure_time(transpose_blocked_64, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Blocked 64x64", time_b64, time_naive / time_b64});
    
    // Cache-oblivious transpose
    cout << "Testing cache-oblivious transpose..." << flush;
    double time_co = measure_time(transpose_cache_oblivious, A, B);
    if (!verify_transpose(A, B)) {
        cout << " FAILED verification!\n";
        return 1;
    }
    cout << " OK\n";
    results.push_back({"Cache Oblivious", time_co, time_naive / time_co});
    
    // Print results
    cout << "\n=================================================\n";
    cout << "  Benchmark Results\n";
    cout << "=================================================\n";
    cout << left << setw(20) << "Algorithm" 
         << right << setw(12) << "Time (ms)" 
         << setw(12) << "Speedup" << endl;
    cout << "-------------------------------------------------\n";
    
    for (const auto& r : results) {
        cout << left << setw(20) << r.name 
             << right << setw(12) << fixed << setprecision(2) << r.time
             << setw(12) << fixed << setprecision(2) << r.speedup << "x" << endl;
    }
    
    cout << "=================================================\n";
    
    return 0;
}