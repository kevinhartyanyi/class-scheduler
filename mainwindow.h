#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
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
    /**
     * @brief build5DayTable: Builds the empty table*/
    void build5DayTable();
    /**
     * @brief printTable: Prints the given TimeTable out*/
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

    void on_sortCombo_currentIndexChanged(int index);

private:
    int getColumnIndex(Days day);
    void setupButtons();
    void setupInfo();
    void printInfo();
    void enableButtons();
    void disableButtons();

    Ui::MainWindow *ui;
    QTableWidget* table;
    Model model;
    size_t tIndex;
    QFont font;
};

#endif // MAINWINDOW_H
