#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "data.h"
#include "model.h"
#include "timetable.h"
#include <array>
#include <random>

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

    void on_actionRecolour_triggered();

    void on_actionBy_Empty_Hours_triggered();

    void on_actionBy_Days_Off_triggered();

    void on_actionReverse_Days_Off_triggered();

    void on_actionReverse_Empty_Hours_triggered();

    void on_actionClear_All_triggered();

    void on_colourButton_clicked();

    void on_sortCombo_currentIndexChanged(int index);

private:
    int getColumnIndex(Days day);
    void setupButtons();
    void setupInfo();
    void printInfo();
    void enableButtons();
    void disableButtons();
    void changeGradient();

    Ui::MainWindow *ui;
    QTableWidget* table;
    Data data;
    Model model;
    size_t tIndex;
    QFont font;
    const std::array<std::pair<QString,QString>, 5> gradients;

    std::random_device r;
    std::mt19937 engine;
    std::uniform_int_distribution<size_t> distr;
};

#endif // MAINWINDOW_H
