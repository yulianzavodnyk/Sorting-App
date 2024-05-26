#include "sorts.h"

// Ініціалізації масиву випадковими числами
int* initialize_random_array(int n, int a, int b) {
    int* arr = new int[n];
    random_device rand; // Пристрій для генерування випадкових чисел
    mt19937 generate(rand()); // Генератор випадкових чисел Mersenne Twister
    uniform_int_distribution<> distribution(a, b); // Розподіл випадкових чисел у межах [a, b]
    for (int i = 0; i < n; i++)
        arr[i] = distribution(generate);
    return arr;
}

// Виведення масиву в консоль
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