#include "timetable.h"
#include <algorithm>
#include <math.h>

std::random_device TimeTable::r;

void TimeTable::add(const QString& name, const Interval& intervals)
{
    tTable.push_back(std::make_pair(name, intervals));
}

int TimeTable::getEmptyHours() const
{
    int emptyHours = 0;
    for (size_t i = 1; i < tTable.size(); ++i)
    {
        if(tTable[i - 1].second.day == tTable[i].second.day) emptyHours += tTable[i].second.start - tTable[i - 1].second.finish;
    }
    return emptyHours;
}

int TimeTable::getDaysOff() const
{
    int daysWork = 1;
    for (size_t i = 1; i < tTable.size(); ++i)
    {
        if(tTable[i - 1].second.day != tTable[i].second.day) daysWork++;
    }
    return 5 - daysWork;
}

void TimeTable::sort()
{
    std::sort(tTable.begin(),tTable.end(),[](const auto& left, const auto& right){return left.second < right.second;});
}

void TimeTable::colourize()
{
    colours.clear();
    colours.reserve(tTable.size());
    const float offset = distr(engine);
    for (size_t i = 0; i < tTable.size(); ++i)
    {
        QColor colour;
        colour.setHsv((fmod(offset + (goldenRatio * i), static_cast <float>(1))) * 360, 76, 240);
        colours.push_back(colour);
    }
}

void TimeTable::printDebug() const
{
    qDebug() << "";
    for (auto& t : tTable)
    {
        qDebug() << t.first << " " << t.second.day2 << " " << t.second.start << " " << t.second.finish;
    }
}
