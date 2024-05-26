#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <string>

using namespace std;

struct Metrics {
    int array_size;
    string sort_name;
    int swap_count;
    int assignment_count;
    size_t used_memory;
    double sort_time;
};

class SortArray {
private:
    int* array;
    int array_size;
    string status;
    Metrics sort_metrics;

    void quick_sort_run(int, int);
    int partition(int, int);

    void merge_sort_run(int, int);
    void merge(int, int, int);

    void heap_sort_run();
    void heapify(int, int);

public:
    SortArray(int*, int);
    SortArray(const SortArray& other);
    SortArray& operator=(const SortArray& other);
    int operator[](int index) const { return array[index]; }
    ~SortArray();

    SortArray quick_sorted();
    SortArray merge_sorted();
    SortArray heap_sorted();

    Metrics get_metrics() { return sort_metrics; }
    int get_size() const { return array_size; }

    void print_metrics();
    void print_array();
};

int* initialize_random_array(int, int, int);

bool is_file_empty(string&);
bool save_metrics_to_csv(string&, Metrics);

#endif