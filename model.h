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
    size_t size() {return timeTables.size();}
    auto& get(size_t idx) const { //TODO: replace get with []
        auto t = timeTables[idx];
        qDebug() << "TTTTTTTTTTTTTTTTTTTTTTTTTT";
        t.printDebug();
        qDebug() << "TTTTTTTTTTTTTTTTTTTTTTTTTT";
        for (int i = 0; i < t.size(); ++i) {
            //qDebug() << t[i].first << " " << t[i].second.start << " " << t[i].second.finish;
        }
        return timeTables[idx];
    }
    auto& operator[](size_t idx) {return timeTables[idx];}

private:    
    auto cartProduct() const;
    auto scheduleTimeTable(TimeTable& tTable);

    std::map<QString, std::set<Interval>> model;
    std::vector<TimeTable> timeTables;
};

#endif // MODEL_H
