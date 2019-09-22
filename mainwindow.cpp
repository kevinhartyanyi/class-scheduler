#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->timeTable;
    build5DayTable();
    QPixmap pixmap(":/rs/images/images/class_schedule_left_arrow.png");
    QIcon ButtonIcon(pixmap);
    ui->leftArrow->setText("");
    ui->leftArrow->setMinimumSize(10,100);
    ui->leftArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_left_arrow.png);");
    ui->rightArrow->setText("");
    ui->rightArrow->setMinimumSize(10,100);
    ui->rightArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_right_arrow.png);");
    //saveTable();
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

void MainWindow::on_newSchedule_triggered()
{
    QString filter = "All file (*.*) ;; Recommended (*.csv *.txt)";
    QString fileName = QFileDialog::getOpenFileName(this, "Open data to schedule", QDir::homePath(), filter);
    if(fileName != "") model.loadModel(fileName);
}

void MainWindow::on_actionSchedule_triggered()
{
    model.schedule();
    printTable(model.get(0));
}

void MainWindow::printTable(const TimeTable& tTable)
{
    for (size_t i = 0; i < tTable.size(); ++i)
    {
        auto& [name, interval] = tTable[i];
        qDebug() << interval.day2;
        QTableWidgetItem* newItem = new QTableWidgetItem(name);
        //table->setItem(2, 1, newItem);
        //qDebug() << name;

    }
}
