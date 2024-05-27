#include "sorts.h"

// Initialize array with random numbers
int* initialize_random_array(int n, int a, int b) {
    int* arr = new int[n];
    random_device rand;                                 // Device for generating random numbers
    mt19937 generate(rand());                       // Mersenne Twister random number generator
    uniform_int_distribution<> distribution(a, b);      // Uniform distribution in the range [a, b]
    for (int i = 0; i < n; i++)
        arr[i] = distribution(generate);
    return arr;
}

// Print array to console
void SortArray::print_array() {
    cout << "\n===================================" << endl;
    cout << left << setw(12) << "Status:" << status << endl;
    cout << left << setw(12) << "Array Size:" << array_size << endl;
    cout << "===================================" << endl;
    cout << left << setw(12) << "Array:";
    for (int i = 0; i < array_size; i++)
        cout << array[i] << " ";
    cout << endl;
    cout << "===================================" << endl;
}