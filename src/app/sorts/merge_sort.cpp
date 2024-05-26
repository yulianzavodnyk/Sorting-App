#include "sorts.h"

// Cортування методом MergeSort та повернення відсортованого масиву
SortArray SortArray::merge_sorted() {
    SortArray result(*this); // Створення копії поточного масиву
    result.sort_metrics = {array_size, "MergeSort", 0, (sizeof(int)*array_size), 0};

    // Вимірювання та обчислення часу сортування
    auto start_time = chrono::high_resolution_clock::now();
    result.merge_sort_run(0, array_size-1); // Виконання сортування
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result; // Повернення відсортованого масиву
}

// Функція для сортування методом MergeSort
void SortArray::merge_sort_run(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Обчислення середини
        merge_sort_run(left, mid); // Cортування лівої частини
        merge_sort_run(mid + 1, right); // Cортування правої частини
        merge(left, mid, right); // Злиття двох частин
    }
}

void SortArray::merge(int left, int mid, int right) {
    int sub_array1 = mid - left + 1;
    int sub_array2 = right - mid;

    // Створення лівого та правого підмасивів
    int* left_array = new int[sub_array1];
    int* right_array = new int[sub_array2];

    copy(array + left, array + left + sub_array1, left_array);
    std::copy(array + mid + 1, array + mid + 1 + sub_array2, right_array);

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