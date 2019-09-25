#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <QString>
#include "interval.h"
#include <QColor>

class TimeTable
{
public:
    TimeTable() {}
    TimeTable(std::vector<std::pair<QString, Interval>>& inctTable): tTable(inctTable) {}
    void add(const QString& name, const Interval& intervals);
    void add(const std::pair<QString, Interval>& entry) {tTable.push_back(entry);}
    void printDebug();
    void sort();
    void colourize();
    QColor getColour(size_t idx) const {return colours[idx];}
    size_t size() const {return tTable.size();}
    const auto& operator[](size_t idx) const {return tTable[idx];}
private:
    unsigned int gradient(float ratio) const;
    std::vector<std::pair<QString, Interval>> tTable;
    std::vector<QColor> colours;
};

#endif // TIMETABLE_H
