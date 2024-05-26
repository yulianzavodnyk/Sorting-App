#include "window.h"
#include "ui_window.h"
#include <vector>

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
    ui->setupUi(this);

    connect(ui->QuickSortButton, &QPushButton::clicked, this, &Window::QuickSortButton_clicked);
    connect(ui->MergeSortButton, &QPushButton::clicked, this, &Window::MergeSortButton_clicked);
    connect(ui->HeapSortButton, &QPushButton::clicked, this, &Window::HeapSortButton_clicked);
    connect(ui->GenerateArrayButton, &QPushButton::clicked, this, &Window::GenerateArrayButton_clicked);
    connect(ui->SaveMetricsButton, &QPushButton::clicked, this, &Window::SaveMetricsButton_clicked);
    connect(ui->InfoButton, &QPushButton::clicked, this, &Window::InfoButton_clicked); // Connect InfoButton

    ui->InputArray->setMaxLength(100000000);
}

Window::~Window() { delete ui; }

void Window::InfoButton_clicked() {
    QMessageBox::information(this, "Info",
         "This application allows you to sort arrays using QuickSort, MergeSort, or HeapSort. "
         "Also you can generate random arrays and view sorting metrics.\n\n"
         "1. If you want to generate array randomly, input size of it and the minimum and maximum possible number you want to be in array. "
         "Size = [1, 100000]; Min = [-10000000, 10000000]; Max = [-10000000, 10000000].\n"
         "2. You can also manually print array. Format: integers separated by commas.\n"
         "3. Choose sorting algorithm: QuickSort, MergeSort, or HeapSort.\n"
         "4. After you press one of sorting buttons you will see sorted array and sorting metrics.\n"
         "5. Then after array sorted, you can download metrics in csv format. To do it, you need to input file path. "
         "There is already default path '../src/evaluation/sorting_metrics.csv', but you can change it."
    );
}

void Window::GenerateArrayButton_clicked() {
    QString size = ui->InputSize->text();
    QString a = ui->InputFirstNum->text();
    QString b = ui->InputSecondNum->text();

    ui->InputArray->clear();
    ui->Metrics->clear();
    ui->SortedArray->clear();
    ui->MetricsSavedMessage->clear();

    if (validate_generate_input(size, a, b)) {
        int array_size = size.toInt();
        int* arr = initialize_random_array(array_size, a.toInt(), b.toInt());

        QStringList inputList;
        for(int i = 0; i < array_size; i++)
            inputList.append(QString::number(arr[i]));

        ui->InputArray->setText(inputList.join(", "));
        delete[] arr;
    }
}

bool Window::validate_generate_input(QString& InputSize, QString& InputFirstNum, QString& InputSecondNum) {
    bool size_is_int, first_num_is_int, second_num_is_int;
    int size = InputSize.toInt(&size_is_int);
    int a = InputFirstNum.toInt(&first_num_is_int);
    int b = InputSecondNum.toInt(&second_num_is_int);

    if(InputSize.isEmpty()) {
        ui->SortedArray->setText("Generation Error: To generate array to must input size.");
        return false;
    }
    else if (!size_is_int || size < 1 || size > 100000) {
        ui->SortedArray->setText("Generation Error: Size must be valid integer from 1 to 100000.");
        return false;
    }
    else if(InputFirstNum == "" || InputSecondNum == "") {
        ui->SortedArray->setText("Generation Error: To generate array you must input both min and max numbers.");
        return false;
    }
    else if (!first_num_is_int || !second_num_is_int) {
        ui->SortedArray->setText("Generation Error: Min and max numbers must be valid.");
        return false;
    }
    else if (a < -1000000 || a > 1000000 || b < -1000000 || b > 1000000) {
        ui->SortedArray->setText("Generation Error: Min and max numbers allows to be only integers from -1000000 to 1000000.");
        return false;
    }
    else if (a > b) {
        ui->SortedArray->setText("Generation Error: Min numbers must be smaller than max numbers.");
        return false;
    }
    return true;
}

void Window::QuickSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.quick_sorted(); });
}

void Window::MergeSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.merge_sorted(); });
}

void Window::HeapSortButton_clicked() {
    sort_and_display([](SortArray arr) { return arr.heap_sorted(); });
}

void Window::sort_and_display(const function<SortArray(SortArray)>& sortFunction) {
    QString input = ui->InputArray->text();
    QStringList inputList = input.split(',');
    ui->MetricsSavedMessage->clear();

    if (validate_input(inputList)) {
        std::vector<int> array;
        for(const QString& number : inputList)
            array.push_back(number.toInt());

        SortArray sortArray(array.data(), array.size());
        SortArray sortedArray = sortFunction(sortArray);

        QString output;
        for(int i = 0; i < sortedArray.get_size(); i++) {
            output.append(QString::number(sortedArray[i]));
            if(i != sortedArray.get_size() - 1)
                output.append(", ");
        }
        ui->SortedArray->setText(output);

        metrics = sortedArray.get_metrics();
        ui->Metrics->setText("Algorithm: " + QString::fromStdString(metrics.sort_name) + "\n" +
                             "Size: " + QString::number(metrics.array_size) + "\n" +
                             "Swaps: " + QString::number(metrics.swap_count) + "\n" +
                             "Assignments: " + QString::number(metrics.assignment_count) + "\n" +
                             "Used Memory: " + QString::number(metrics.used_memory) + "\n" +
                             "Time: " + QString::fromStdString(to_string(metrics.sort_time)) + " seconds\n");
    }
}

bool Window::validate_input(QStringList& inputList) {
    for (QString& str : inputList) {
        bool is_int;
        str.toInt(&is_int);
        if (!is_int) {
            ui->SortedArray->setText("Input Error: Please enter valid integers separated by commas.");
            ui->Metrics->clear();
            return false;
        }
    }
    return true;
}


void Window::SaveMetricsButton_clicked() {
    string file_path = ui->SavedPath->text().toStdString();
    QString metricsMessage = ui->MetricsSavedMessage->text();
    if (metricsMessage != "Metrics successfully saved!") {
        QString metricsText = ui->Metrics->toPlainText();
        if(metrics.sort_name.empty() || metricsText == "")
            ui->MetricsSavedMessage->setText("No metrics to saved");
        else if(save_metrics_to_csv(file_path, metrics))
            ui->MetricsSavedMessage->setText("Metrics successfully saved!");
        else
            ui->MetricsSavedMessage->setText("Error opening file!");
    }
}