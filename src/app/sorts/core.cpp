#include "sorts.h"

SortArray::SortArray(int* arr, int size) : array_size(size), status("Unsorted"), sort_metrics({size, "None (Not sorted yet)", 0, 0, 0, 0}) {
    array = new int[array_size];
    copy(arr, arr + array_size, array);
}

SortArray::SortArray(const SortArray& other) : array_size(other.array_size), status(other.status), sort_metrics(other.sort_metrics) {
    array = new int[array_size];
    copy(other.array, other.array + array_size, array);
}

SortArray& SortArray::operator=(const SortArray& other) {
    if (this != &other) {
        delete[] array;
        array_size = other.array_size;
        status = other.status;
        array = new int[array_size];
        copy(other.array, other.array + array_size, array);
        sort_metrics = other.sort_metrics;
    }
    return *this;
}

SortArray::~SortArray() {delete[] array;}