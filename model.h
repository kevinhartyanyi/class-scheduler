#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <set>
#include <string>
#include "interval.h"
#include <QString>
#include <vector>
#include <timetable.h>

class Model
{

public:
    Model() {}
    void loadModel(const QString& fileName);
    void schedule();
    auto get(size_t idx) const {return timeTables[idx];}

private:    
    auto cartProduct() const;
    auto scheduleTimeTable(TimeTable& tTable);

    std::map<QString, std::set<Interval>> model;
    std::vector<TimeTable> timeTables;
};

#endif // MODEL_H
