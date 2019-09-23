#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <QString>
#include "interval.h"

class TimeTable
{
public:
    TimeTable() {}
    TimeTable(std::vector<std::pair<QString, Interval>>& inctTable): tTable(inctTable) {}
    void add(const QString& name, const Interval& intervals);
    void add(const std::pair<QString, Interval>& entry) {tTable.push_back(entry);}
    void printDebug();
    void sort();
    size_t size() const {return tTable.size();}
    const auto& operator[](size_t idx) const {return tTable[idx];}
private:
    std::vector<std::pair<QString, Interval>> tTable;
};

#endif // TIMETABLE_H
