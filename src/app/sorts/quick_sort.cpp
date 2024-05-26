#include "sorts.h"

// Сортування методом QuickSort та повернення відсортованого масиву
SortArray SortArray::quick_sorted() {
    SortArray result(*this); // Створення копії поточного масиву
    result.sort_metrics = {array_size, "QuickSort", 0, (sizeof(int)*array_size), 0};

    // Вимірювання та обчислення часу сортування
    auto start_time = chrono::high_resolution_clock::now();
    result.quick_sort_run(0, result.array_size - 1); // Виконання сортування
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result; // Повернення відсортованого масиву
}

// Функція для сортування методом QuickSort
void SortArray::quick_sort_run(int low, int high) {
    if (low < high) {
        int p = partition(low,high); // Розділення масиву та отримання індекса розділювача
        quick_sort_run(low,p-1); // Сортування лівої частини
        quick_sort_run(p+1, high); // Сортування правої частини
    }
}

// Функція для розділення масиву та повернення індексу розділювача
int SortArray::partition(int low, int high) {
    int pivot = array[high]; // Вибір опорного елемента
    int i = (low-1);

    for (int j = low; j <= high; j++) {
        if (array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
            sort_metrics.swap_count++;
        }
    }
    swap(array[i+1], array[high]);
    sort_metrics.swap_count++;
    return (i+1); // Повернення індексу розділювача
}