#include "sorts.h"

SortArray SortArray::merge_sorted() {
    SortArray result(*this);
    result.sort_metrics = {array_size, "MergeSort", 0, 0, (sizeof(int)*array_size), 0};

    auto start_time = chrono::high_resolution_clock::now();
    result.merge_sort_run(0, array_size-1);
    auto end_time = chrono::high_resolution_clock::now();
    result.sort_metrics.sort_time = chrono::duration<double>(end_time - start_time).count();

    result.status = "Sorted";
    return result;
}

void SortArray::merge_sort_run(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_run(left, mid);
        merge_sort_run(mid + 1, right);
        merge(left, mid, right);
    }
}

void SortArray::merge(int left, int mid, int right) {
    int sub_array1 = mid - left + 1;
    int sub_array2 = right - mid;

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
        sort_metrics.assignment_count++;
    }

    while (i < sub_array1) {
        array[k] = left_array[i];
        i++;
        k++;
        sort_metrics.assignment_count++;
    }

    while (j < sub_array2) {
        array[k] = right_array[j];
        j++;
        k++;
        sort_metrics.assignment_count++;
    }

    delete[] left_array;
    delete[] right_array;
}