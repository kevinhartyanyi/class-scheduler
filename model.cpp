#include "model.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

void Model::loadModel(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) QMessageBox::information(nullptr, "Error", file.errorString());

    QTextStream text(&file);

    while(!text.atEnd())
    {
        QString line = text.readLine();
        QStringList fields = line.split(",");
        if (fields.count() <= 1)
        {
            QMessageBox::information(nullptr, "Error", "Every item must contain at least one time interval");
            return;
        }
        QString fieldName;
        std::set<Interval> intervalSet;

        // First item is the name of the activity
        fieldName = fields[0];

        for(int i = 1; i < fields.size(); ++i)
        {
            auto rawInterval = fields[i].split('-');
            intervalSet.insert(rawInterval);
        }
        model.emplace(fieldName, intervalSet);
    }
    file.close();
}

auto Model::cartProduct() const
{
    std::vector<std::vector<std::pair<QString, Interval>>> allLines;
    for (auto& course : model)
    {
        std::vector<std::pair<QString, Interval>> temp;
        for (auto& intervals : course.second)
        {
            auto pair = std::make_pair(course.first, intervals);
            temp.push_back(pair);
        }
        allLines.push_back(temp);
    }

    std::vector<std::vector<std::pair<QString, Interval>>> allProduct = {{}};

        for (const auto& group : allLines)
        {
            std::vector<std::vector<std::pair<QString,Interval>>> collect;

            for (const auto& pre : allProduct)
            {
                for (const auto& val : group)
                {
                    collect.push_back(pre);
                    collect.back().push_back(val);
                }
            }
            allProduct = move(collect);
        }
        std::vector<TimeTable> tTable;
        for (auto& vPairs : allProduct)
        {
            tTable.push_back(vPairs);
        }
        return tTable;
}

auto Model::scheduleTimeTable(TimeTable& tTable)
{
    TimeTable ret;
    // Sort jobs according to finish time

    // The first activity always gets selected
    size_t i = 0;
    ret.add(tTable[0]);
    // Consider rest of the activities
    for (size_t j = 1; j < tTable.size(); j++)
    {
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it

        // If start time is bigger than the last's finish or it's a different day, then add it (works because of the sorting)
        if (tTable[j].second.start >= tTable[i].second.finish || tTable[j].second.day != tTable[i].second.day)
        {
            ret.add(tTable[j]);
            i = j;
        }
    }
    return ret;
}

void Model::schedule()
{
    auto allProduct = cartProduct();
    timeTables.clear();
    for (auto& tTable : allProduct)
    {
        auto stTable = scheduleTimeTable(tTable);
        stTable.colourize();
        timeTables.push_back(stTable);
    }
}

void Model::sortByEmptyHours()
{
    std::sort(timeTables.begin(), timeTables.end(),[](const auto& left, const auto& right){return left.getEmptyHours() < right.getEmptyHours();});
}
void Model::sortByDaysOff()
{
    std::sort(timeTables.begin(), timeTables.end(),[](const auto& left, const auto& right){return left.getDaysOff() > right.getDaysOff();});
}
void Model::sortByEmptyHoursReverse()
{
    std::sort(timeTables.begin(), timeTables.end(),[](const auto& left, const auto& right){return left.getEmptyHours() > right.getEmptyHours();});
}
void Model::sortByDaysOffReverse()
{
    std::sort(timeTables.begin(), timeTables.end(),[](const auto& left, const auto& right){return left.getDaysOff() < right.getDaysOff();});
}

