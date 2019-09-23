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
    ui->leftArrow->setAction(ui->actionPrevious);
    ui->rightArrow->setText("");
    ui->rightArrow->setMinimumSize(10,100);
    ui->rightArrow->setStyleSheet("border-image:url(:/rs/images/images/class_schedule_right_arrow.png);");
    ui->rightArrow->setAction(ui->actionNext);
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
        table->setItem(interval.start - 8, getColumnIndex(interval.day), newItem);
        table->setSpan(interval.start - 8, getColumnIndex(interval.day), interval.finish - interval.start, 1);
    }
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
