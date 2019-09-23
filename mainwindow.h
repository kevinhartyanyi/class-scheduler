#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "data.h"
#include "model.h"
#include "timetable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void build5DayTable();
    void printTable(const TimeTable& tTable);
    ~MainWindow();

private slots:
    void on_newSchedule_triggered();
    void on_actionSchedule_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

private:
    int getColumnIndex(Days day);

    Ui::MainWindow *ui;
    QTableWidget* table;
    Data data;
    Model model;
    size_t tIndex;
};

#endif // MAINWINDOW_H
