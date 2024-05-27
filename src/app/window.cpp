#include "window.h"
#include "ui_window.h"
#include <vector>

// Constructor for the Window class
Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);

    // Connecting signals to slots
    connect(ui->QuickSortButton, &QPushButton::clicked, this, &Window::QuickSortButton_clicked);
    connect(ui->MergeSortButton, &QPushButton::clicked, this, &Window::MergeSortButton_clicked);
    connect(ui->HeapSortButton, &QPushButton::clicked, this, &Window::HeapSortButton_clicked);
    connect(ui->GenerateArrayButton, &QPushButton::clicked, this, &Window::GenerateArrayButton_clicked);
    connect(ui->SaveMetricsButton, &QPushButton::clicked, this, &Window::SaveMetricsButton_clicked);
    connect(ui->InfoButton, &QPushButton::clicked, this, &Window::InfoButton_clicked); // Connect InfoButton

    ui->InputArray->setMaxLength(1000000); // Reset maximum input length
}

// Destructor for the Window class
Window::~Window() { delete ui; }

// Handler for Info button click
void Window::InfoButton_clicked() {
    QMessageBox::information(this, "Info",
                             "This application allows you to sort arrays using QuickSort, MergeSort, or HeapSort. "
                             "You can also generate random arrays and view sorting metrics.\n\n"
                             "1. To generate an array randomly, input its size and the minimum and maximum possible values. "
                             "Size = [1, 100000]; Min = [-1000000, 1000000]; Max = [-1000000, 1000000].\n"
                             "2. You can also manually input an array. Format: integers separated by commas.\n"
                             "3. Choose a sorting algorithm: QuickSort, MergeSort, or HeapSort.\n"
                             "4. After pressing one of the sorting buttons, you will see the sorted array and sorting metrics.\n"
                             "5. Once the array is sorted, you can download the metrics in CSV format. To do this, you need to input a file path. "
                             "There is a default path 'src/evaluation/sorting_metrics.csv', but you can change it."
    );
}

// Handler for Generate button click
void Window::GenerateArrayButton_clicked() {
    // Reading input data
    QString size = ui->InputSize->text();
    QString a = ui->InputFirstNum->text();
    QString b = ui->InputSecondNum->text();

    // Clearing input and output fields
    ui->InputArray->clear();
    ui->Metrics->clear();
    ui->SortedArray->clear();
    ui->MetricsSavedMessage->clear();

    // Validating input parameters
    if (validate_input_generate_params(size, a, b)) {
        int array_size = size.toInt();
        int* arr = initialize_random_array(array_size, a.toInt(), b.toInt());

        // Creating a string of the generated array and setting it in InputArray
        QStringList inputList;
        for (int i = 0; i < array_size; i++)
            inputList.append(QString::number(arr[i]));

        ui->InputArray->setText(inputList.join(", "));
        delete[] arr;
    }
}

// Validate parameters for generating the array
bool Window::validate_input_generate_params(QString& InputSize, QString& InputFirstNum, QString& InputSecondNum) {
    bool size_is_int, first_num_is_int, second_num_is_int;
    int size = InputSize.toInt(&size_is_int);
    int a = InputFirstNum.toInt(&first_num_is_int);
    int b = InputSecondNum.toInt(&second_num_is_int);

    if (InputSize.isEmpty())
        ui->SortedArray->setText("Generation Error: You must input the size to generate an array.");
    else if (!size_is_int || size < 1 || size > 100000)
        ui->SortedArray->setText("Generation Error: Size must be a valid integer between 1 and 100000.");
    else if (InputFirstNum.isEmpty() || InputSecondNum.isEmpty())
        ui->SortedArray->setText("Generation Error: You must input both minimum and maximum numbers to generate an array.");
    else if (!first_num_is_int || !second_num_is_int)
        ui->SortedArray->setText("Generation Error: Minimum and maximum numbers must be valid integers.");
    else if (a < -1000000 || a > 1000000 || b < -1000000 || b > 1000000)
        ui->SortedArray->setText("Generation Error: Minimum and maximum numbers must be between -1000000 and 1000000.");
    else if (a > b)
        ui->SortedArray->setText("Generation Error: Minimum number must be less than the maximum number.");
    else
        return true;
    return false;
}

// Handler for QuickSort button click
void Window::QuickSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.quick_sorted(); });
}

// Handler for MergeSort button click
void Window::MergeSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.merge_sorted(); });
}

// Handler for HeapSort button click
void Window::HeapSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.heap_sorted(); });
}

// Sort and display the array
void Window::sort_and_display(const function<SortArray(SortArray)>& sortFunction) {
    QString input = ui->InputArray->text();
    QStringList inputList = input.split(',');
    ui->MetricsSavedMessage->clear();
    if (validate_input(inputList)) {
        // Convert input data into a vector of integers
        std::vector<int> array;
        for (const QString& number : inputList)
            array.push_back(number.toInt());

        // Create and sort the array
        SortArray sortArray(array.data(), array.size());
        SortArray sortedArray = sortFunction(sortArray);

        // Create a string of the sorted array
        QString output;
        for (int i = 0; i < sortedArray.get_size(); i++) {
            output.append(QString::number(sortedArray[i]));
            if (i != sortedArray.get_size() - 1)
                output.append(", ");
        }
        ui->SortedArray->setText(output);

        // Get and display sorting metrics
        metrics = sortedArray.get_metrics();
        ui->Metrics->setText("Algorithm: " + QString::fromStdString(metrics.sort_name) + "\n" +
                             "Array Size: " + QString::number(metrics.array_size) + "\n" +
                             "Swaps: " + QString::number(metrics.swap_count) + "\n" +
                             "Used Memory: " + QString::number(metrics.used_memory) + "\n" +
                             "Time: " + QString::fromStdString(to_string(metrics.sort_time)) + " seconds\n");
    }
    else {
        ui->SortedArray->setText("Input Error: Please enter valid integers separated by commas.");
        ui->Metrics->clear();
    }
}

// Validate the input array
bool Window::validate_input(QStringList& inputList) {
    for (QString& str : inputList) {
        bool is_int;
        str.toInt(&is_int);
        if (!is_int)
            return false;
    }
    return true;
}

// Handler for Save Metrics button click
void Window::SaveMetricsButton_clicked() {
    string file_path = ui->SavedPath->text().toStdString();
    QString metricsMessage = ui->MetricsSavedMessage->text();
    QString metricsText = ui->Metrics->toPlainText();

    // Check if there are metrics to save
    if (metrics.sort_name.empty() || metricsText.isEmpty())
        ui->MetricsSavedMessage->setText("No metrics to save.");
    // Save metrics to a CSV file
    else if (save_metrics_to_csv(file_path, metrics))
        ui->MetricsSavedMessage->setText("Metrics successfully saved!");
    else
        ui->MetricsSavedMessage->setText("Error opening file!");
}
