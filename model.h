#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <set>
#include <string>
#include "interval.h"
#include <QString>
#include <vector>
#include <timetable.h>
#include <QtDebug>

class Model
{

public:
    Model() {}
    void loadModel(const QString& fileName);
    void schedule();
    void sortByEmptyHours();
    void sortByDaysOff();
    void sortByDaysOffReverse();
    void sortByEmptyHoursReverse();
    void clear() {timeTables.clear(); model.clear();}
    size_t size() const {return timeTables.size();}
    auto& operator[](size_t idx) {return timeTables[idx];}

private:
    /**
     * @brief cartProduct: Calculates the cartesian product of this->model and returns it*/
    auto cartProduct() const;
    auto scheduleTimeTable(TimeTable& tTable);

    std::map<QString, std::set<Interval>> model;
    std::vector<TimeTable> timeTables;
};

#endif // MODEL_H
