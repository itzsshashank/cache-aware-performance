// Naive matrix transpose implementation
// No cache optimization - accesses memory with poor spatial locality

const int N = 2048;

void transpose_naive(double A[N][N], double B[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}
