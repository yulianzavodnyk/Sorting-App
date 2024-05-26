
#include <QApplication>
#include "app/window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}

/*int main() {
    bool a;
    string file_path = "../src/evaluation/sorting_metrics.csv";
    for(int i = 0; i < 10000000; i += 1000000) {
        int* arr = initialize_random_array(i, 0, i);
        SortArray unsortedArray(arr, i);
        SortArray Quick = unsortedArray.quick_sorted();
        arr = initialize_random_array(i, 0, i);
        SortArray unsortedArray1(arr, i);
        SortArray Merge = unsortedArray1.merge_sorted();
        arr = initialize_random_array(i, 0, i);
        SortArray unsortedArray2(arr, i);
        SortArray Heap = unsortedArray2.heap_sorted();
        a = save_metrics_to_csv(file_path, Quick.get_metrics());
        a = save_metrics_to_csv(file_path, Merge.get_metrics());
        a = save_metrics_to_csv(file_path, Heap.get_metrics());
    }
}*/