#include "sorts.h"

int* initialize_random_array(int n, int a, int b) {
    int* arr = new int[n];
    random_device rand;
    mt19937 generate(rand());
    uniform_int_distribution<> distribution(a, b);
    for(int i = 0; i < n; i++)
        arr[i] = distribution(generate);
    return arr;
}

void SortArray::print_array() {
    cout << "\n===================================" << endl;
    cout << left << setw(12) << "Status:" << status << endl;
    cout << left << setw(12) << "Array Size:" << array_size << endl;
    cout << "===================================" << endl;
    cout << left << setw(12) << "Array:";
    for(int i = 0; i < array_size; i++)
        cout << array[i] << " ";
    cout << endl;
    cout << "===================================" << endl;
}