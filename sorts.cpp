#include <cstring>
#include <functional>

void insertion_sort(int* a, int n) {
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

void insertion_sort_optimized(int* a, int n) {
    int* end = a + n;
    for (int* i = a + 1; i < end; ++i) {
        int key = *i;
        if (*(i - 1) <= key) continue;
        int* pos = std::upper_bound(a, i, key);
        memmove(pos + 1, pos, (i - pos) * sizeof(int));
        *pos = key;
    }
}
