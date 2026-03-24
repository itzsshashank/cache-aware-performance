// Blocked (tiled) matrix transpose implementations
// Uses cache blocking to improve spatial and temporal locality

const int N = 2048;

// 8x8 blocking
void transpose_blocked_8(double A[N][N], double B[N][N]) {
    const int BLOCK_SIZE = 8;
    
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            // Transpose the block
            for (int bi = i; bi < i + BLOCK_SIZE && bi < N; bi++) {
                for (int bj = j; bj < j + BLOCK_SIZE && bj < N; bj++) {
                    B[bj][bi] = A[bi][bj];
                }
            }
        }
    }
}

// 16x16 blocking
void transpose_blocked_16(double A[N][N], double B[N][N]) {
    const int BLOCK_SIZE = 16;
    
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            // Transpose the block
            for (int bi = i; bi < i + BLOCK_SIZE && bi < N; bi++) {
                for (int bj = j; bj < j + BLOCK_SIZE && bj < N; bj++) {
                    B[bj][bi] = A[bi][bj];
                }
            }
        }
    }
}

// 32x32 blocking
void transpose_blocked_32(double A[N][N], double B[N][N]) {
    const int BLOCK_SIZE = 32;
    
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            // Transpose the block
            for (int bi = i; bi < i + BLOCK_SIZE && bi < N; bi++) {
                for (int bj = j; bj < j + BLOCK_SIZE && bj < N; bj++) {
                    B[bj][bi] = A[bi][bj];
                }
            }
        }
    }
}

// 64x64 blocking
void transpose_blocked_64(double A[N][N], double B[N][N]) {
    const int BLOCK_SIZE = 64;
    
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            // Transpose the block
            for (int bi = i; bi < i + BLOCK_SIZE && bi < N; bi++) {
                for (int bj = j; bj < j + BLOCK_SIZE && bj < N; bj++) {
                    B[bj][bi] = A[bi][bj];
                }
            }
        }
    }
}
