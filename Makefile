CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall -Wextra
LDFLAGS = 

# Target executable
TARGET = transpose_benchmark

# Source files
SOURCES = main.cpp naive_transpose.cpp blocked_transpose.cpp cache_oblivious_transpose.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Build directory
BUILD_DIR = build

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Link the executable
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the benchmark
run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

# Run with perf (Linux only)
perf: $(BUILD_DIR)/$(TARGET)
	perf stat -e cache-references,cache-misses,cycles,instructions ./$(BUILD_DIR)/$(TARGET)

# Run with detailed cache stats (Linux only)
perf-cache: $(BUILD_DIR)/$(TARGET)
	perf stat -e L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses ./$(BUILD_DIR)/$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS)
	rm -rf $(BUILD_DIR)

# Clean and rebuild
rebuild: clean all

.PHONY: all run perf perf-cache clean rebuild
