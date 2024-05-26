#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include "sorts/sorts.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

// Клас Window, що наслідує QMainWindow
class Window : public QMainWindow {
    Q_OBJECT

// Слоти, що викликаються при натисканні відповідних кнопок
private slots:
    void InfoButton_clicked();  // Обробка натискання кнопки Info
    void GenerateArrayButton_clicked();  // Обробка натискання кнопки Generate
    void QuickSortButton_clicked();  // Обробка натискання кнопки QuickSort
    void MergeSortButton_clicked();  // Обробка натискання кнопки MergeSort
    void HeapSortButton_clicked();  // Обробка натискання кнопки HeapSort
    void SaveMetricsButton_clicked();  // Обробка натискання кнопки Save Metrics

private:
    Ui::Window *ui;  // Вказівник на інтерфейс користувача
    Metrics metrics;  // Зберігання метрик сортування

    void sort_and_display(const function<SortArray(SortArray)>&);  // Сортування та відображення масиву
    bool validate_input(QStringList&);  // Валідація введеного масиву
    bool validate_input_generate_params(QString&, QString&, QString&);  // Валідація параметрів для генерації масиву

public:
    // Конструктор
    explicit Window(QWidget *parent = nullptr);
    // Деструктор
    ~Window() override;
};

#endif