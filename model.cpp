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
        bool first = true;
        for (auto field : fields)
        {
            if(first)
            {
                fieldName = field;
                first = false;
                continue;
            }
            auto rawInterval = field.split('-');
            intervalSet.insert(rawInterval);
        }
        model.emplace(fieldName, intervalSet);
    }
    file.close();

    /*for (auto v : model) {
        qDebug() << v.first << endl;
        for (auto& t : v.second) {
            qDebug() << t.day2 << " " << t.start << " " << t.finish << endl;
        }
    }*/
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
    tTable.sort();

    // The first activity always gets selected
    size_t i = 0;
    ret.add(tTable[0]);
    // Consider rest of the activities
    for (size_t j = 1; j < tTable.size(); j++)
    {
        /*if(tTable[i].second < tTable[j].second)
        {
            qDebug() << "Earlier: " << tTable[i].second.day2 << " " << tTable[i].second.start << " " << tTable[i].second.finish;
            qDebug() << "Later: " << tTable[j].second.day2 << " " << tTable[j].second.start << " " << tTable[j].second.finish;

        }
        else {
            qDebug() << "No";
        }*/
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it

        if (tTable[j].second.start >= tTable[i].second.finish)
        {
            ret.add(tTable[j]);
            i = j;
        }

        //TODO: Test for different days
        //if(tTable[j].second.start >= tTable[i].second.finish && tTable[j].second.day == tTable[i].second.day)
        /*
        if (tTable[j].second >= tTable[i].second)
        {
            ret.add(tTable[j]);
            i = j;
        }*/
    }
    return ret;
}

void Model::schedule()
{
    auto allProduct = cartProduct();
    timeTables.clear();
    for (auto& tTable : allProduct)
    {
        timeTables.push_back(scheduleTimeTable(tTable));
    }
}
