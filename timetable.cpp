#include "timetable.h"
#include <algorithm>

void TimeTable::add(const QString& name, const Interval& intervals)
{
    tTable.push_back(std::make_pair(name, intervals));
}

void TimeTable::sort()
{
    std::sort(tTable.begin(),tTable.end(), [](const auto& left, const auto& right){return left.second < right.second;});
}
