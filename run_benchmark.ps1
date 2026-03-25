# Cache-Aware Performance Benchmark Script (Windows)
# Run comprehensive benchmarks

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "Cache-Aware Performance Benchmark Suite" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

# Build the project
Write-Host "Building project..." -ForegroundColor Yellow
if (Test-Path "build\transpose_benchmark.exe") {
    Remove-Item "build\transpose_benchmark.exe" -Force
}

# Try to use MinGW g++ if available
if (Get-Command g++ -ErrorAction SilentlyContinue) {
    Write-Host "Using g++ compiler..." -ForegroundColor Green
    g++ -std=c++11 -O3 -Wall -Wextra main.cpp naive_transpose.cpp blocked_transpose.cpp cache_oblivious_transpose.cpp -o build\transpose_benchmark.exe
} elseif (Get-Command cl -ErrorAction SilentlyContinue) {
    Write-Host "Using MSVC compiler..." -ForegroundColor Green
    if (-not (Test-Path "build")) {
        New-Item -ItemType Directory -Path "build" | Out-Null
    }
    cl /EHsc /O2 /Fe:build\transpose_benchmark.exe main.cpp naive_transpose.cpp blocked_transpose.cpp cache_oblivious_transpose.cpp
} else {
    Write-Host "No C++ compiler found! Please install MinGW or MSVC." -ForegroundColor Red
    exit 1
}

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Build successful!" -ForegroundColor Green
Write-Host ""

# Run basic benchmark
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "Running benchmark..." -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

if (Test-Path "build\transpose_benchmark.exe") {
    .\build\transpose_benchmark.exe
} else {
    Write-Host "Executable not found!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Benchmark complete!" -ForegroundColor Green
