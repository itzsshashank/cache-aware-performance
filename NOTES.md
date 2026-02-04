## Cache line size
- Cache line size is **64 bytes**
- Memory is transferred between memory hierarchy levels in fixed-size cache lines
- A single load brings an entire 64B block into the cache, not just one element

---

## L1, L2, L3 cache sizes
- **L1 cache**: ~1.2 MB total
- **L2 cache**: ~11.5 MB total
- **L3 cache**: ~24.0 MB total
- Cache sizes determine the maximum working set that can be accessed with low latency

---

## Sequential memory access
- Access pattern: increasing, contiguous memory addresses
- Each access benefits from **spatial locality**
- One cache miss brings in multiple future elements (within the same 64B line)
- Hardware prefetchers detect the pattern and fetch upcoming cache lines in advance
- After initial misses, most accesses hit in **L1 or L2 cache**
- Memory latency is largely hidden; performance approaches peak bandwidth

---

## Strided access (stride > cache line)
- Each access touches a **different cache line**
- Spatial locality is lost
- Every access likely causes a cache miss at the current level
- Hardware prefetchers are less effective or disabled
- Cache bandwidth is underutilized
- Latency increases sharply when the working set exceeds cache capacity
- Cache level boundaries (L1 → L2 → L3 → DRAM) become clearly observable
- Useful for exposing true cache latency and replacement behavior in microbenchmarks
