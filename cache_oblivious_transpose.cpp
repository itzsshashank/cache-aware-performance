// Cache-oblivious matrix transpose
// Uses recursive divide-and-conquer to automatically adapt to cache hierarchy
// No hardcoded block sizes - works well across different cache sizes

const int N = 2048;
const int CUTOFF = 16;  // Base case threshold

void transpose_recursive(double A[N][N], double B[N][N], 
                        int row_start, int row_end,
                        int col_start, int col_end) {
    int rows = row_end - row_start;
    int cols = col_end - col_start;
    
    // Base case: small enough to transpose directly
    if (rows <= CUTOFF && cols <= CUTOFF) {
        for (int i = row_start; i < row_end; i++) {
            for (int j = col_start; j < col_end; j++) {
                B[j][i] = A[i][j];
            }
        }
        return;
    }
    
    // Recursive case: divide and conquer
    if (rows >= cols) {
        // Split horizontally
        int mid = row_start + rows / 2;
        transpose_recursive(A, B, row_start, mid, col_start, col_end);
        transpose_recursive(A, B, mid, row_end, col_start, col_end);
    } else {
        // Split vertically
        int mid = col_start + cols / 2;
        transpose_recursive(A, B, row_start, row_end, col_start, mid);
        transpose_recursive(A, B, row_start, row_end, mid, col_end);
    }
}

void transpose_cache_oblivious(double A[N][N], double B[N][N]) {
    transpose_recursive(A, B, 0, N, 0, N);
}
