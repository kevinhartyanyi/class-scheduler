#include "interval.h"
#include <iostream>

Interval::Interval(QStringList interval)
{
    start = interval.first().toInt();
    finish = interval.last().toInt();
}
