#ifndef INTERVAL_H
#define INTERVAL_H

#include <QStringList>
#include <QDebug>
#include "days.h"

struct Interval
{
    int start;
    int finish;
    Days day;
    QString day2; // For debugging
    Interval(QStringList interval);
};

inline bool operator== (const Interval& left, const Interval& right){
    return left.start == right.start && left.finish == right.finish && left.day == right.day;
}

inline bool operator< (const Interval& left, const Interval& right){
    return left.day < right.day || (left.day == right.day && left.finish < right.finish);
}
inline bool operator> (const Interval& left, const Interval& right){return  operator< (right,left);}
inline bool operator<=(const Interval& left, const Interval& right){return !operator> (left,right);}
inline bool operator>=(const Interval& left, const Interval& right){return !operator< (left,right);}
inline bool operator!=(const Interval& left, const Interval& right){return !operator==(left,right);}

inline std::ostream& operator<<(std::ostream& os, const Interval& intval)
{
    os << "(" << intval.start << ", " << intval.finish << ")";
    return os;
}

#endif // INTERVAL_H
