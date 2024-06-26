#include "sorts.h"

// Constructor
SortArray::SortArray(int* arr, int size) {
    array_size = size;
    array = new int[array_size];
    copy(arr, arr + array_size, array);
    sort_metrics = {size, "None (Not sorted yet)", 0, 0, 0};
    status = "Unsorted";
}

// Destructor
SortArray::~SortArray() { delete[] array; }

// Copy constructor
SortArray::SortArray(const SortArray& other) {
    array_size = other.array_size;
    array = new int[array_size];
    copy(other.array, other.array + array_size, array);
    sort_metrics = other.sort_metrics;
    status = other.status;
}

// Assignment operator
SortArray& SortArray::operator=(const SortArray& other) {
    // Check for self-assignment
    if (this != &other) {
        delete[] array;
        array_size = other.array_size;
        array = new int[array_size];
        copy(other.array, other.array + array_size, array);
        sort_metrics = other.sort_metrics;
        status = other.status;
    }
    return *this;
}