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
