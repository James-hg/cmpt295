// CMPT 295 Mini-Project – Insertion Sort Performance Analysis

#include <algorithm>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

const int SPACING = 15;
const int TRIALS = 5;
const int RNG_SEED = 0;
static mt19937 rng(RNG_SEED);

struct Pattern {
    string name;
    function<void(vector<int>&)> fill_func;
};

/* Sort variants */
void insertion_sort_arr(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

void insertion_sort_vec(vector<int>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = key;
    }
}

void insertion_sort_optimized(int* a, int n) {
    int* end = a + n;
    for (int* i = a + 1; i < end; i++) {
        int key = *i;
        // if already in order with previous, skip
        if (*(i - 1) <= key) continue;

        // Binary search to find the insertion point
        int* pos = std::upper_bound(a, i, key);

        // Eliminates the inner loop branch mispredictions
        memmove(pos + 1, pos, (i - pos) * sizeof(int));

        *pos = key;
    }
}

/* Input patterns */

// Fills with increasing int
void fill_sorted(vector<int>& v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = i;
    }
}

// Fills with decreasing int
void fill_reverse(vector<int>& v) {
    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = v.size() - 1 - i;
    }
}

// Fills with random int
void fill_random(vector<int>& v) {
    uniform_int_distribution<> dis(1, 1000000);

    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = dis(rng);
    }
}

// Fills vector with duplicates
void fill_many_duplicates(vector<int>& v) {
    uniform_int_distribution<> dis(0, 5);

    for (unsigned int i = 0; i < v.size(); i++) {
        v[i] = dis(rng);
    }
}

/* Timing methods with averages */

double time_insertion_sort_arr(const Pattern& pat, int n) {
    double total_ms = 0.0;
    for (int t = 0; t < TRIALS; t++) {
        vector<int> v(n);
        pat.fill_func(v);
        auto start = chrono::high_resolution_clock::now();
        insertion_sort_arr(v.data(), n);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        total_ms += elapsed.count();
    }
    return total_ms / TRIALS;
}

double time_insertion_sort_vec(const Pattern& pat, int n) {
    double total_ms = 0.0;
    for (int t = 0; t < TRIALS; t++) {
        vector<int> v(n);
        pat.fill_func(v);
        auto start = chrono::high_resolution_clock::now();
        insertion_sort_vec(v);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        total_ms += elapsed.count();
    }
    return total_ms / TRIALS;
}

double time_insertion_sort_opt(const Pattern& pat, int n) {
    double total_ms = 0.0;
    for (int t = 0; t < TRIALS; t++) {
        vector<int> v(n);
        pat.fill_func(v);
        auto start = chrono::high_resolution_clock::now();
        insertion_sort_optimized(v.data(), n);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        total_ms += elapsed.count();
    }
    return total_ms / TRIALS;
}

double time_std_sort(const Pattern& pat, int n) {
    double total_ms = 0.0;
    for (int t = 0; t < TRIALS; t++) {
        vector<int> v(n);
        pat.fill_func(v);
        auto start = chrono::high_resolution_clock::now();
        sort(v.begin(), v.end());
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;
        total_ms += elapsed.count();
    }
    return total_ms / TRIALS;
}

// Display benchmark results
void benchmark() {
    // Test sizes as requested
    vector<int> sizes = {1000, 5000, 10000, 20000, 50000};

    // Define patterns to test (fill methods)
    vector<Pattern> patterns = {{"sorted", fill_sorted},
                                {"reverse", fill_reverse},
                                {"random", fill_random},
                                {"duplicates", fill_many_duplicates}};

    // table header
    cout << setw(SPACING + 5) << "sort name" << setw(SPACING) << "fill method"
         << setw(SPACING) << "# of ele" << setw(SPACING + 5)
         << "elapsed (avg ms)" << endl;

    // test different sizes with different patterns
    for (int n : sizes) {
        for (const Pattern& pat : patterns) {
            // arr
            double arr_ms = time_insertion_sort_arr(pat, n);
            cout << setw(SPACING + 5) << "insertion_sort_arr" << setw(SPACING)
                 << pat.name << setw(SPACING) << n << setw(SPACING + 5)
                 << arr_ms << endl;

            // vec
            double vec_ms = time_insertion_sort_vec(pat, n);
            cout << setw(SPACING + 5) << "insertion_sort_vec" << setw(SPACING)
                 << pat.name << setw(SPACING) << n << setw(SPACING + 5)
                 << vec_ms << endl;

            // optimized
            double opt_ms = time_insertion_sort_opt(pat, n);
            cout << setw(SPACING + 5) << "insertion_sort_opt" << setw(SPACING)
                 << pat.name << setw(SPACING) << n << setw(SPACING + 5)
                 << opt_ms << endl;

            // std sort
            double std_ms = time_std_sort(pat, n);
            cout << setw(SPACING + 5) << "std::sort" << setw(SPACING)
                 << pat.name << setw(SPACING) << n << setw(SPACING + 5)
                 << std_ms << endl
                 << endl;
        }
        cout << endl;
    }
}

int main() {
    benchmark();
    return 0;
}
