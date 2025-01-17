#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
#include <QFileDialog>
#include <QDir>
#include <QDesktopWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->timeTable;
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7); // At start show the application with 70% of the screen size
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    build5DayTable();
    disableButtons();

    int fontId = QFontDatabase::addApplicationFont(":/rs/fonts/fonts/Vollkorn/Vollkorn-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    font.setFamily(family);
    font.setBold(true);
    font.setWeight(QFont::Bold);

    setupButtons();
    setupInfo();
}

void MainWindow::setupInfo()
{
    ui->info->setRowCount(2);
    ui->info->setColumnCount(2);
    ui->info->verticalHeader()->hide();
    ui->info->setStyleSheet("gridline-color: white;");
    ui->info->setEditTriggers(QAbstractItemView::NoEditTriggers);
    font.setBold(false);
    QTableWidgetItem* property = new QTableWidgetItem("Property");
    property->setFont(font);
    ui->info->setHorizontalHeaderItem(0, property);
    QTableWidgetItem* value = new QTableWidgetItem("Value");
    value->setFont(font);
    ui->info->setHorizontalHeaderItem(1, value);
    ui->info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->info->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupButtons()
{
    QPixmap pixmap(":/rs/images/images/class_schedule_left_arrow.png");
    QIcon ButtonIcon(pixmap);
    ui->leftArrow->setMinimumSize(100,100);
    ui->leftArrow->setMaximumSize(200,200);
    ui->leftArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_left_arrow.png);");
    ui->leftArrow->setAction(ui->actionPrevious);    
    ui->leftArrow->setText("");

    ui->rightArrow->setMinimumSize(100,100);
    ui->rightArrow->setMaximumSize(200,200);
    ui->rightArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_right_arrow.png);");
    ui->rightArrow->setAction(ui->actionNext);    
    ui->rightArrow->setText("");

    ui->middleButton->setAction(ui->actionSchedule);
    ui->middleButton->setText(ui->actionSchedule->text());
}


void MainWindow::build5DayTable()
{
    auto workDays = {"Monday", "Tuesday", "Wednday", "Thursday", "Friday"};
    auto workHours = {"8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"};

    table->setRowCount(static_cast<int>(workHours.size()));
    table->setColumnCount(static_cast<int>(workDays.size()));
    table->horizontalHeader()->setMinimumHeight(50);

    int hCount = 0;

    font.setBold(true);
    font.setWeight(QFont::Bold);

    for(auto day : workDays)
    {
        QTableWidgetItem* hDay = new QTableWidgetItem(tr(day));
        hDay->setFont(font);
        table->setHorizontalHeaderItem(hCount, hDay);
        ++hCount;
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    hCount = 0;
    for(auto hours : workHours)
    {
        QTableWidgetItem* hDay = new QTableWidgetItem(tr(hours));
        hDay->setFont(font);
        table->setVerticalHeaderItem(hCount, hDay);
        ++hCount;
    }
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printInfo()
{
    font.setBold(false);
    QTableWidgetItem* emptyTime = new QTableWidgetItem("Empty time between classes:");
    emptyTime->setFont(font);
    ui->info->setItem(0,0, emptyTime);

    QTableWidgetItem* emptyTimeValue = new QTableWidgetItem(QString::number(model[tIndex].getEmptyHours()) + " hours");
    emptyTimeValue->setFont(font);
    ui->info->setItem(0,1, emptyTimeValue);

    QTableWidgetItem* daysOff = new QTableWidgetItem("Days off:");
    daysOff->setFont(font);
    ui->info->setItem(1,0, daysOff);

    QTableWidgetItem* daysOffValue = new QTableWidgetItem(QString::number(model[tIndex].getDaysOff()) + " days");
    daysOffValue->setFont(font);
    ui->info->setItem(1,1, daysOffValue);
}

void MainWindow::enableButtons()
{
    ui->actionNext->setEnabled(true);
    ui->actionPrevious->setEnabled(true);
    ui->actionClear_All->setEnabled(true);
    ui->actionRecolour->setEnabled(true);    
    ui->actionSchedule->setEnabled(true);
    ui->menuSort->setEnabled(true);
    ui->sortCombo->setEnabled(true);
    ui->menuActions->setEnabled(true);
}
void MainWindow::disableButtons()
{
    ui->actionNext->setEnabled(false);
    ui->actionPrevious->setEnabled(false);
    ui->actionClear_All->setEnabled(false);
    ui->actionRecolour->setEnabled(false);
    ui->actionSchedule->setEnabled(false);
    ui->menuSort->setEnabled(false);
    ui->menuActions->setEnabled(false);
    ui->sortCombo->setEnabled(false);
}

void MainWindow::printTable(const TimeTable& tTable)
{
    table->clearContents();
    table->clearSpans();
    for (size_t i = 0; i < tTable.size(); ++i)
    {
        auto& [name, interval] = tTable[i];
        QTableWidgetItem* newItem = new QTableWidgetItem(name);
        newItem->setBackground(tTable.getColour(i));
        table->setItem(interval.start - 8, getColumnIndex(interval.day), newItem);
        if(interval.finish - interval.start > 1)
            table->setSpan(interval.start - 8, getColumnIndex(interval.day), interval.finish - interval.start, 1);
    }
    printInfo();
}

int MainWindow::getColumnIndex(Days day)
{
    switch (day)
    {
        case Days::Monday:
            return 0;
        case Days::Tuesday:
            return 1;
        case Days::Wednesday:
            return 2;
        case Days::Thursday:
            return 3;
        case Days::Friday:
            return 4;
        case Days::Saturday:
            return 5;
        case Days::Sunday:
            return 6;

    }
}

void MainWindow::on_actionNext_triggered()
{
    if(tIndex == model.size() - 1) return;
    ++tIndex;
    printTable(model[tIndex]);
}

void MainWindow::on_actionPrevious_triggered()
{
    if(tIndex == 0) return;
    --tIndex;
    printTable(model[tIndex]);
}

void MainWindow::on_actionRecolour_triggered()
{
    auto& tTable = model[tIndex];
    tTable.colourize();
    printTable(tTable);
}

void MainWindow::on_actionBy_Empty_Hours_triggered()
{
    tIndex = 0;
    model.sortByEmptyHours();
    printTable(model[tIndex]);
}

void MainWindow::on_actionBy_Days_Off_triggered()
{
    tIndex = 0;
    model.sortByDaysOff();
    printTable(model[tIndex]);
}

void MainWindow::on_actionReverse_Days_Off_triggered()
{
    tIndex = 0;
    model.sortByDaysOffReverse();
    printTable(model[tIndex]);
}

void MainWindow::on_actionReverse_Empty_Hours_triggered()
{
    tIndex = 0;
    model.sortByEmptyHoursReverse();
    printTable(model[tIndex]);
}

void MainWindow::on_actionClear_All_triggered()
{
    model.clear();
    table->clearContents();
    ui->info->clearContents();
    disableButtons();
}

void MainWindow::on_newSchedule_triggered()
{
    QString filter = "Recommended (*.csv *.txt) ;; All file (*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, "Open data to schedule", QDir::homePath(), filter);
    if(fileName != "")
    {
        model.loadModel(fileName);
        enableButtons();
    }
}

void MainWindow::on_actionSchedule_triggered()
{
    tIndex = 0;
    model.schedule();
    printTable(model[tIndex]);
}


void MainWindow::on_sortCombo_currentIndexChanged(int index)
{
    if(index == 0) on_actionBy_Empty_Hours_triggered();    
    else if(index == 1) on_actionBy_Days_Off_triggered();
    else if(index == 2) on_actionReverse_Empty_Hours_triggered();
    else if(index == 3) on_actionReverse_Days_Off_triggered();
}
