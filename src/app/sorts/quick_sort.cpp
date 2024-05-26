#include "sorts.h"

SortArray SortArray::quick_sorted() {
    SortArray result(*this);
    result.sort_metrics = {array_size, "QuickSort", 0, 0, (sizeof(int)*array_size), 0};

    auto start_time = chrono::high_resolution_clock::now();
    result.quick_sort_run(0, result.array_size - 1);
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();


    result.status = "Sorted";
    return result;
}

void SortArray::quick_sort_run(int low, int high) {
    if(low < high) {
        int p = partition(low,high);
        quick_sort_run(low,p-1);
        quick_sort_run(p+1, high);
    }
}

int SortArray::partition(int low, int high) {
    int pivot = array[high];
    int i = (low-1);

    for(int j = low; j <= high; j++) {
        if(array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
            sort_metrics.swap_count++;
            sort_metrics.assignment_count += 3;
        }
    }
    swap(array[i+1], array[high]);
    sort_metrics.swap_count++;
    sort_metrics.assignment_count += 3;
    return (i+1);
}