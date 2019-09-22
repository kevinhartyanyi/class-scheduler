#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QTableWidget>

class Data
{
public:
    void saveTable(QTableWidget* table, QString separator, QString saveName);
};

#endif // DATA_H
