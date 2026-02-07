# Insertion Sort Performance Analyzer

This project, **Insertion Sort Performance Analyzer**, is a benchmarking and analysis tool for evaluating the performance of different insertion sort implementations in C++. It was developed as a course project for CMPT 295 by James Hoang.

## Project Overview

The project compares three variants of insertion sort:

- `insertion_sort_arr`: Standard insertion sort on C-style arrays
- `insertion_sort_vec`: Standard insertion sort on C++ vectors
- `insertion_sort_opt`: Optimized insertion sort using binary search and `memmove`
- `std::sort`: C++ Standard Library sort (for baseline comparison)

Each variant is tested on multiple input patterns:

- Sorted
- Reverse sorted
- Random
- Many duplicates

Performance is measured in milliseconds over several trials and for various input sizes (1,000 to 50,000 elements).

## Features

- Modular C++ code for easy extension and experimentation
- Automated benchmarking with multiple trials
- Assembly output for each optimization level (O0, O2, O3)
- Cachegrind and performance logs for deeper analysis

## Usage

1. **Build the project:**

- Compile with different optimization flags (e.g., `-O0`, `-O2`, `-O3`) to generate different binaries and assembly outputs.
- Example:

   ```sh
   g++ -O2 -o sort_o2 main.cpp sorts.cpp
   ```

1. **Run the benchmark:**

- Execute the binary to print timing results to the console.
- Example:

   ```sh
   ./sort_o2 > results_o2.txt
   ```

1. **Analyze results:**

- Compare output files (`results_o0.txt`, `results_o2.txt`, `results_o3.txt`) and performance logs.
- Review assembly files (`sorts_o0.S`, `sorts_o2.S`, `sorts_o3.S`) for code generation differences.
- Use `cachegrind` for cache/memory analysis.

## File Structure

- `main.cpp` — Benchmarking and timing logic
- `sorts.cpp` — Insertion sort implementations
- `sorts_o0.S`, `sorts_o2.S`, `sorts_o3.S` — Assembly outputs for each optimization level
- `results_o0.txt`, `results_o2.txt`, `results_o3.txt` — Benchmark results
- `perf_o0.txt`, `perf_o2.txt`, `perf_o3.txt` — Performance logs
- `cachegrind.out.*`, `cg_log.txt` — Cachegrind profiler outputs
- `assembly_notes.txt` — (Optional) Notes on assembly analysis

## Example Results

Sample output (O2 optimization, 1,000 elements, random input):

| Sort Variant         | Time (ms) |
|----------------------|-----------|
| insertion_sort_arr   |   0.27    |
| insertion_sort_vec   |   0.34    |
| insertion_sort_opt   |   0.19    |
| std::sort            |   0.11    |

See the `results_o*.txt` and `perf_o*.txt` files for full benchmarks.

## Author

James Hoang

---
*CMPT 295 Mini-Project – Insertion Sort Performance Analyzer*
