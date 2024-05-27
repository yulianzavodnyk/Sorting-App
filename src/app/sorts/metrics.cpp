#include "sorts.h"

// Print sorting metrics to the console
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

// Check if a file is empty
bool is_file_empty(string& file_path) {
    ifstream file(file_path, ios::ate);     // Open file in append mode
    return file.tellg() == 0;                        // Check if the file size is zero
}

// Save metrics to a CSV file
bool save_metrics_to_csv(string& file_path, Metrics metrics) {
    ofstream file(file_path, ios::app);     // Open file in append mode

    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return false;
    }

    // Write headers to the file if it is empty
    if (is_file_empty(file_path))
        file << "Algorithm,Array Size,Swaps,Used Memory,Time\n";

    // Write metrics to the file
    file << metrics.sort_name + "," +
            to_string(metrics.array_size) + "," +
            to_string(metrics.swap_count) + "," +
            to_string(metrics.used_memory) + "," +
            to_string(metrics.sort_time) + "\n";

    cout << "Metrics successfully saved!\n";

    file.close();   // Close the file
    return true;
}