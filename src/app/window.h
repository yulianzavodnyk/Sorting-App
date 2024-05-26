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

class Window : public QMainWindow {
Q_OBJECT
private slots:
    void QuickSortButton_clicked();
    void MergeSortButton_clicked();
    void HeapSortButton_clicked();
    void GenerateArrayButton_clicked();
    void SaveMetricsButton_clicked();
    void InfoButton_clicked();

private:
    Ui::Window *ui;
    Metrics metrics;

    void sort_and_display(const function<SortArray(SortArray)>&);
    bool validate_input(QStringList&);
    bool validate_generate_input(QString&, QString&, QString&);

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;
};

#endif