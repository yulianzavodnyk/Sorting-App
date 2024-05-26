#include "sorts.h"

// Сортування методом HeapSort та повернення відсортованого масиву
SortArray SortArray::heap_sorted() {
    SortArray result(*this); // Створення копії поточного масиву
    result.sort_metrics = {array_size, "Heap Sort", 0, (sizeof(int)*array_size), 0};

    // Вимірювання та обчислення часу сортування
    auto start_time = chrono::high_resolution_clock::now();
    result.heap_sort_run(); // Виконання сортування
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result; // Повернення відсортованого масиву
}

// Функція для сортування методом HeapSort
void SortArray::heap_sort_run() {
    // Створення купи
    for (int i = array_size/2-1; i >= 0; i--)
        heapify(array_size, i);

    for (int i = array_size-1; i > 0; i--) {
        swap(array[0], array[i]); // Переміщення кореня в кінець
        sort_metrics.swap_count++;
        heapify(i, 0); // Повторна побудова купи
    }
}

void SortArray::heapify(int heap_size, int root_index) {
    int largest_element = root_index;
    int left_child = 2*root_index+1;
    int right_child = 2*root_index+2;

    // Перевірка, чи лівий або правий дочірній елемент більший за корінь
    if (left_child < heap_size && array[left_child] > array[largest_element])
        largest_element = left_child;
    if (right_child < heap_size && array[right_child] > array[largest_element])
        largest_element = right_child;

    if (largest_element != root_index) {
        swap(array[root_index], array[largest_element]);
        sort_metrics.swap_count++;
        heapify(heap_size, largest_element);
    }
}