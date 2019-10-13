#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <QString>
#include "interval.h"
#include <QColor>
#include <random>

class TimeTable
{
public:
    TimeTable(): engine(r()),  distr(0, 1) {}
    TimeTable(std::vector<std::pair<QString, Interval>>& inctTable): tTable(inctTable), engine(r()),  distr(0, 1) {}

    void add(const QString& name, const Interval& intervals);
    void add(const std::pair<QString, Interval>& entry) {tTable.push_back(entry);}
    /**
     * @brief printDebug: Only for debugging*/
    void printDebug() const;
    /**
     * @brief sort: Sort the values in this->tTable based on the Intervals*/
    void sort();
    /**
     * @brief colourize: Clear and fill this->colours with new colours,
     * using the goldenRatio to get evenly placed gradient values*/
    void colourize();
    /**
     * @brief getEmptyHours: Returns the time between intervals in hours*/
    int getEmptyHours() const;
    /**
     * @brief getDaysOff: Returns the number of days when there aren't any intervals*/
    int getDaysOff() const; // Only call after sort
    const QColor getColour(size_t idx) const {return colours[idx];}
    size_t size() const {return tTable.size();}
    const auto& operator[](size_t idx) const {return tTable[idx];}
private:
    std::vector<std::pair<QString, Interval>> tTable;
    std::vector<QColor> colours;
    static std::random_device r;
    std::mt19937 engine;
    std::uniform_real_distribution<float> distr;
    constexpr static float goldenRatio = 0.618033988749895f;
};

#endif // TIMETABLE_H
