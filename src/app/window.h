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

// Class Window inheriting from QMainWindow
class Window : public QMainWindow {
    Q_OBJECT

// Slots triggered by respective button clicks
private slots:
    void InfoButton_clicked();                // Handler for Info button click
    void GenerateArrayButton_clicked();       // Handler for Generate button click
    void QuickSortButton_clicked();           // Handler for QuickSort button click
    void MergeSortButton_clicked();           // Handler for MergeSort button click
    void HeapSortButton_clicked();            // Handler for HeapSort button click
    void SaveMetricsButton_clicked();         // Handler for Save Metrics button click

private:
    Ui::Window *ui;                           // Pointer to the user interface
    Metrics metrics;                          // Storage for sorting metrics

    // Helper functions
    void sort_and_display(const function<SortArray(SortArray)>&);       // Sort and display the array
    bool validate_input(QStringList&);                                  // Validate the input array
    bool validate_input_generate_params(QString&, QString&, QString&);  // Validate parameters for generating the array

public:
    explicit Window(QWidget *parent = nullptr);     // Constructor
    ~Window() override;                             // Destructor
};

#endif
