#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Structure to store sorting metrics
struct Metrics {
    int array_size;
    string sort_name;
    int swap_count;
    size_t used_memory;
    double sort_time;
};

// Class to handle arrays and their sorting
class SortArray {
private:
    int* array;
    int array_size;
    string status;
    Metrics sort_metrics;

    // Functions for QuickSort implementation
    void quick_sort_run(int, int);
    int partition(int, int);
    // Functions for MergeSort implementation
    void merge_sort_run(int, int);
    void merge(int, int, int);
    // Functions for HeapSort implementation
    void heap_sort_run();
    void heapify(int, int);

public:

    SortArray(int*, int);               // Constructor
    SortArray(const SortArray& other);  // Copy constructor
    ~SortArray();                       // Destructor


    SortArray& operator=(const SortArray& other);               // Assignment operator
    int operator[](int index) const { return array[index]; }    // Operator to access array elements

    // Functions to sort the array using different algorithms
    SortArray quick_sorted();
    SortArray merge_sorted();
    SortArray heap_sorted();

    // Functions to get sorting metrics and array size
    Metrics get_metrics() { return sort_metrics; }
    int get_size() { return array_size; }

    // Functions to print metrics and array to console
    void print_metrics();
    void print_array();
};


int* initialize_random_array(int, int, int);    // Initialize array with random numbers

bool is_file_empty(string&);                    // Check if a file is empty
bool save_metrics_to_csv(string&, Metrics);     // Save sorting metrics to a CSV file

#endif
