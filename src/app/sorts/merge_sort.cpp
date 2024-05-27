#include "sorts.h"

// Sort the array using MergeSort and return the sorted array
SortArray SortArray::merge_sorted() {
    SortArray result(*this);    // Create a copy of the current array
    result.sort_metrics = {array_size, "MergeSort", 0, (sizeof(int) * array_size), 0};

    // Measure and calculate the sorting time
    auto start_time = chrono::high_resolution_clock::now();
    result.merge_sort_run(0, array_size - 1);       // Run array sorting
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result;      // Return the sorted array
}

// Function to perform MergeSort
void SortArray::merge_sort_run(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;    // Calculate the middle
        merge_sort_run(left, mid);          // Sort the left part
        merge_sort_run(mid + 1, right);     // Sort the right part
        merge(left, mid, right);                // Merge the two parts
    }
}

// Function to merge two subarrays
void SortArray::merge(int left, int mid, int right) {
    int sub_array1 = mid - left + 1;
    int sub_array2 = right - mid;

    // Create left and right subarrays
    int* left_array = new int[sub_array1];
    int* right_array = new int[sub_array2];

    copy(array + left, array + left + sub_array1, left_array);
    copy(array + mid + 1, array + mid + 1 + sub_array2, right_array);

    sort_metrics.used_memory += sizeof(int) * (sub_array1 + sub_array2);

    int i = 0, j = 0, k = left;
    while (i < sub_array1 && j < sub_array2) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < sub_array1) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < sub_array2) {
        array[k] = right_array[j];
        j++;
        k++;
    }

    delete[] left_array;
    delete[] right_array;
}
