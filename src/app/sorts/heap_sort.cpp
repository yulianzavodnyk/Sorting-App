#include "sorts.h"

SortArray SortArray::heap_sorted() {
    SortArray result(*this);
    result.sort_metrics = {array_size, "Heap Sort", 0, 0, (sizeof(int)*array_size), 0};

    auto start_time = chrono::high_resolution_clock::now();
    result.heap_sort_run();
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result;
}

void SortArray::heap_sort_run() {
    for(int i = array_size/2-1; i >= 0; i--)
        heapify(array_size, i);

    for(int i = array_size-1; i > 0; i--) {
        swap(array[0], array[i]);
        sort_metrics.swap_count++;
        sort_metrics.assignment_count += 3;
        heapify(i, 0);
    }
}

void SortArray::heapify(int heap_size, int root_index) {
    int largest_element = root_index;
    int left_child = 2*root_index+1;
    int right_child = 2*root_index+2;

    if(left_child < heap_size && array[left_child] > array[largest_element])
        largest_element = left_child;
    if(right_child < heap_size && array[right_child] > array[largest_element])
        largest_element = right_child;

    if(largest_element != root_index) {
        swap(array[root_index], array[largest_element]);
        sort_metrics.swap_count++;
        sort_metrics.assignment_count += 3;
        heapify(heap_size, largest_element);
    }
}