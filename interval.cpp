#include "interval.h"
#include <iostream>

//TODO: Remove day2
Interval::Interval(QStringList interval)
{
    auto daySplit = interval.first().split(':');
    auto& dayName = daySplit.first();
    if(dayName == "Monday" || dayName == "0"){ day2 = "Monday";day = Days::Monday;}
    else if(dayName == "Tuesday" || dayName == "1"){ day2 = "Tuesday";day = Days::Tuesday;}
    else if(dayName == "Wednesday" || dayName == "2"){ day2 = "Wednesday";day = Days::Wednesday;}
    else if(dayName == "Thursday" || dayName == "3"){ day2 = "Thursday";day = Days::Thursday;}
    else if(dayName == "Friday" || dayName == "4"){ day2 = "Friday";day = Days::Friday;}
    else if(dayName == "Saturday" || dayName == "5"){ day2 = "Saturday";day = Days::Saturday;}
    else if(dayName == "Sunday" || dayName == "6"){ day2 = "Sunday";day = Days::Sunday;}

    start = daySplit.last().toInt();
    finish = interval.last().toInt();
}
