#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Структура для зберігання метрик сортування
struct Metrics {
    int array_size;
    string sort_name;
    int swap_count;
    size_t used_memory;
    double sort_time;
};

// Клас для роботи з масивом та їх сортуванням
class SortArray {
private:
    int* array;
    int array_size;
    string status;
    Metrics sort_metrics;

    // Функції для реалізації QuickSort
    void quick_sort_run(int, int);
    int partition(int, int);
    // Функції для реалізації MergeSort
    void merge_sort_run(int, int);
    void merge(int, int, int);
    // Функції для реалізації HeapSort
    void heap_sort_run();
    void heapify(int, int);

public:
    // Конструктор з параметрами
    SortArray(int*, int);
    // Копіювальний конструктор
    SortArray(const SortArray& other);
    // Деструктор
    ~SortArray();

    // Оператор присвоєння
    SortArray& operator=(const SortArray& other);
    // Оператор доступу до елементів масиву
    int operator[](int index) const { return array[index]; }

    // Функції сортування масиву різними алгоритмами
    SortArray quick_sorted();
    SortArray merge_sorted();
    SortArray heap_sorted();

    // Функції отримання метрик сортування та розміру масива
    Metrics get_metrics() { return sort_metrics; }
    int get_size() { return array_size; }

    // Функції виведення метрик та масиву в консоль
    void print_metrics();
    void print_array();
};

// Ініціалізація масиву випадковими числами
int* initialize_random_array(int, int, int);

// Перевірка, чи є файл порожнім
bool is_file_empty(string&);
// Збереження метрик сортування у CSV файл
bool save_metrics_to_csv(string&, Metrics);

#endif