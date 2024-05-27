#include "sorts.h"

// Sort the array using HeapSort and return the sorted array
SortArray SortArray::heap_sorted() {
    SortArray result(*this);    // Create a copy of the current array
    result.sort_metrics = {array_size, "Heap Sort", 0, (sizeof(int) * array_size), 0};

    // Measure and calculate the sorting time
    auto start_time = chrono::high_resolution_clock::now();
    result.heap_sort_run();     // Run srray sorting
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result;      // Return the sorted array
}

// Function to perform HeapSort
void SortArray::heap_sort_run() {
    // Build the heap
    for (int i = array_size / 2 - 1; i >= 0; i--)
        heapify(array_size, i);

    // Extract elements from the heap one by one
    for (int i = array_size - 1; i > 0; i--) {
        swap(array[0], array[i]);   // Move the root to the end
        sort_metrics.swap_count++;
        heapify(i, 0);  // Rebuild the heap
    }
}

// Function to heapify a subtree rooted at root_index
void SortArray::heapify(int heap_size, int root_index) {
    int largest_element = root_index;
    int left_child = 2 * root_index + 1;
    int right_child = 2 * root_index + 2;

    // Check if the left or right child is larger than the root
    if (left_child < heap_size && array[left_child] > array[largest_element])
        largest_element = left_child;
    if (right_child < heap_size && array[right_child] > array[largest_element])
        largest_element = right_child;

    // If the largest element is not the root, swap and continue heapifying
    if (largest_element != root_index) {
        swap(array[root_index], array[largest_element]);
        sort_metrics.swap_count++;
        heapify(heap_size, largest_element);
    }
}
