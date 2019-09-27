#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
#include <QFileDialog>
#include <QDir>
#include <cstdlib>
#include <ctime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->timeTable;
    build5DayTable();

    int fontId = QFontDatabase::addApplicationFont(":/rs/fonts/fonts/Vollkorn/Vollkorn-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family);
    font.setBold(true);
    font.setWeight(QFont::Bold);
    ui->info2->setRowCount(2);
    ui->info2->setColumnCount(2);
    ui->info2->verticalHeader()->hide();
    ui->info2->setStyleSheet("gridline-color: white;");

    srand (static_cast <unsigned> (time(nullptr)));
    setupButtons();

    //saveTable();
}

void MainWindow::setupButtons()
{
    QPixmap pixmap(":/rs/images/images/class_schedule_left_arrow.png");
    QIcon ButtonIcon(pixmap);
    ui->leftArrow->setText("");
    ui->leftArrow->setMinimumSize(10,100);
    ui->leftArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_left_arrow.png);");
    ui->leftArrow->setAction(ui->actionPrevious);
    ui->rightArrow->setText("");
    ui->rightArrow->setMinimumSize(10,100);
    ui->rightArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_right_arrow.png);");
    ui->rightArrow->setAction(ui->actionNext);
}

void MainWindow::build5DayTable()
{
    auto workDays = {"Monday", "Tuesday", "Wednday", "Thursday", "Friday"};
    auto workHours = {"8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"};

    table->setRowCount(14);
    table->setColumnCount(5);
    table->horizontalHeader()->setMinimumHeight(50);

    int hCount = 0;
    int fontId = QFontDatabase::addApplicationFont(":/rs/fonts/fonts/Vollkorn/Vollkorn-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(family);
    font.setBold(true);
    font.setWeight(QFont::Bold);

    for(auto day : workDays)
    {
        QTableWidgetItem* hDay = new QTableWidgetItem(tr(day));
        hDay->setFont(font);
        table->setHorizontalHeaderItem(hCount, hDay);
        ++hCount;
    }
    table->horizontalHeader()->resizeSections(QHeaderView::Stretch);

    hCount = 0;
    for(auto hours : workHours)
    {
        qDebug() << hCount;
        QTableWidgetItem* hDay = new QTableWidgetItem(tr(hours));
        hDay->setFont(font);
        table->setVerticalHeaderItem(hCount, hDay);
        ++hCount;
    }
    table->verticalHeader()->resizeSections(QHeaderView::Stretch);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printInfo()
{
    QTableWidgetItem* freeTime = new QTableWidgetItem("Free time between classes:");
    ui->info2->setItem(0,0, freeTime);
    QTableWidgetItem* daysOff = new QTableWidgetItem("Days off:");
    ui->info2->setItem(1,0, daysOff);

    ui->info->addItem("Free time between classes: ");
    ui->info->addItem("Days off: ");
}

void MainWindow::on_newSchedule_triggered()
{
    QString filter = "All file (*.*) ;; Recommended (*.csv *.txt)";
    QString fileName = QFileDialog::getOpenFileName(this, "Open data to schedule", QDir::homePath(), filter);
    if(fileName != "") model.loadModel(fileName);
}

void MainWindow::on_actionSchedule_triggered()
{
    tIndex = 0;
    model.schedule();
    printTable(model.get(tIndex));
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
    printTable(model.get(tIndex));
}

void MainWindow::on_actionPrevious_triggered()
{
    if(tIndex == 0) return;
    --tIndex;
    printTable(model.get(tIndex));
}

void MainWindow::on_actionRecolour_triggered()
{
    auto& tTable = model[tIndex];
    tTable.colourize();
    printTable(tTable);
}
