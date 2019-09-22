#ifndef INTERVAL_H
#define INTERVAL_H

#include <QStringList>

struct Interval
{
    int start;
    int finish;
    Interval(QStringList interval);
};

inline bool operator== (const Interval& left, const Interval& right){
    return left.start == right.start && left.finish == right.finish;
}

inline bool operator< (const Interval& left, const Interval& right){
    return left.finish < right.finish;
}

inline std::ostream& operator<<(std::ostream& os, const Interval& intval)
{
    os << "(" << intval.start << ", " << intval.finish << ")";
    return os;
}

#endif // INTERVAL_H
