#include "timetable.h"
#include <algorithm>
#include <math.h>
#include <cstdlib>

void TimeTable::add(const QString& name, const Interval& intervals)
{
    tTable.push_back(std::make_pair(name, intervals));
}

void TimeTable::sort()
{
    std::sort(tTable.begin(),tTable.end(),[](const auto& left, const auto& right){return left.second < right.second;});
}

void TimeTable::colourize()
{
    colours.clear();
    colours.reserve(tTable.size());
    qDebug() << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCc";
    for (size_t i = 0; i < tTable.size(); ++i)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        qDebug() << "Offset: " << r;
        qDebug() << "Offset + GoldR: " << r + (0.618033988749895f * i);
        qDebug() << "Fmod: " << fmod(r + (0.618033988749895f * i), float(1));
        qDebug() << "Gradient:" << gradient(fmod(r + (0.618033988749895f * i), float(1)));
        QColor colour;
        colour.setRgb(gradient(fmod(r + (0.618033988749895f * i), float(1))));
        colours.push_back(colour);
    }
    qDebug() << "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCc";
}

unsigned int TimeTable::gradient(float ratio) const
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long
    int normalized = int(ratio * 256 * 6);

    //find the distance to the start of the closest region
    int x = normalized % 256;

    int red = 0, grn = 0, blu = 0;
    switch(normalized / 256)
    {
        case 0: red = 255;      grn = x;        blu = 0;       break;//red
        case 1: red = 255 - x;  grn = 255;      blu = 0;       break;//yellow
        case 2: red = 0;        grn = 255;      blu = x;       break;//green
        case 3: red = 0;        grn = 255 - x;  blu = 255;     break;//cyan
        case 4: red = x;        grn = 0;        blu = 255;     break;//blue
        case 5: red = 255;      grn = 0;        blu = 255 - x; break;//magenta
    }

    return red + (grn << 8) + (blu << 16);
}

void TimeTable::printDebug()
{
    for (auto& t : tTable)
    {
        qDebug() << t.first << " " << t.second.day2 << " " << t.second.start << " " << t.second.finish;
    }
}
