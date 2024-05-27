#include "sorts.h"

// Sort the array using QuickSort and return the sorted array
SortArray SortArray::quick_sorted() {
    SortArray result(*this);    // Create a copy of the current array
    result.sort_metrics = {array_size, "QuickSort", 0, (sizeof(int) * array_size), 0};

    // Measure and calculate the sorting time
    auto start_time = chrono::high_resolution_clock::now();
    result.quick_sort_run(0, result.array_size - 1);    // Run array sorting
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result;      // Return the sorted array
}

// Function to perform QuickSort
void SortArray::quick_sort_run(int low, int high) {
    if (low < high) {
        int p = partition(low, high);            // Partition the array and get the pivot index
        quick_sort_run(low, p - 1);         // Sort the left part
        quick_sort_run(p + 1, high);        // Sort the right part
    }
}

// Function to partition the array and return the pivot index
int SortArray::partition(int low, int high) {
    int pivot = array[high];    // Select the pivot element
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        if (array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
            sort_metrics.swap_count++;
        }
    }
    swap(array[i + 1], array[high]);
    sort_metrics.swap_count++;
    return (i + 1);     // Return the pivot index
}