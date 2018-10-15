//
//  month.h
//  Calendar Sheet
//
//  Created by Erich Küster on January 31, 2016
//  Copyright © 2016 Erich Kuester. All rights reserved.

#ifndef MONTH_H
#define MONTH_H

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class Gregorian;

class Month {
// fill month matrix with the strings for the weeks
public:
    string nameOfMonth = "";
    int daysInMonth = 0;
    int firstWeekday = 0;
    std::vector<std::vector<string>> weekScheme;
    // argument is first of month
    Month(Gregorian* first);
};

#endif /* MONTH_H */
