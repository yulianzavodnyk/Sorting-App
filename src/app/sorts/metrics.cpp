#include "sorts.h"

// Виведення метрик сортування в консоль
void SortArray::print_metrics() {
    cout << "\n===================================" << endl;
    cout << left << setw(12) << "Sort Name:" << sort_metrics.sort_name << endl;
    cout << "===================================" << endl;
    cout << left << setw(12) << "Array Size" << array_size << endl;
    cout << left << setw(12) << "Swaps" << sort_metrics.swap_count << endl;
    cout << left << setw(12) << "Used Memory" << sort_metrics.used_memory << endl;
    cout << left << setw(12) << "Time" << sort_metrics.sort_time << " seconds" << endl;
    cout << "===================================\n";
}

// Перевірки чи файл є порожнім
bool is_file_empty(string& file_path) {
    ifstream file(file_path, ios::ate); // Відкриття файлу в режимі додавання
    return file.tellg() == 0; // Перевірка чи розмір файлу дорівнює нулю
}

// Збереження метрик у файл CSV
bool save_metrics_to_csv(string& file_path, Metrics metrics) {
    ofstream file(file_path, ios::app); // Відкриття файлу в режимі додавання

    if (!file.is_open()) {
        cerr << "Error opening file " << endl;
        return false;
    }

    // Запис заголовків у файл, якщо він порожній
    if (is_file_empty(file_path))
        file << "Algorithm,Array Size,Swaps,Used Memory,Time\n";

    // Запис метрик у файл
    file << metrics.sort_name + "," +
            to_string(metrics.array_size) + "," +
            to_string(metrics.swap_count) + "," +
            to_string(metrics.used_memory) + "," +
            to_string(metrics.sort_time) + "\n";

    cout << "Metrics successfully saved!\n";

    // Закриття файлу
    file.close();
    return true;
}