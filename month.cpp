//
//  month.cpp
//  Calendar Sheet
//
//  Created by Erich Küster on January 31, 2016
//  Copyright © 2016 Erich Kuester. All rights reserved.

#include <vector>
#include "month.h"
#include "gregorian.h"

using namespace std;

Month::Month(Gregorian* first) {
    Glib::ustring months[12] = {"Januar", "Februar", "März", "April", "Mai",
        "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"};
    int m = std::get<1>(first->yeardate) - 1;
    nameOfMonth = months[m];
    // 0 = Mon, 1 = Tue ... 6 = Sun because Monday shall be beginning of the week,
    // God rested the seventh day
    firstWeekday = first->weekday();
    // calculate days in actual month
    Gregorian lastDay = *first + 31;
    unsigned d = get<2>(lastDay.yeardate) - 1;
    daysInMonth = 31 - d;
    // month scheme with 6 weeks a 7 days
    string spaces(3, ' ');
    int w = firstWeekday;
    std::vector<string> week;
    int z = 0;
    // write leading spaces
    while (w != 0) {
        z += 1;
        week.push_back(spaces);
        if ((z % 7) == 0) {
            weekScheme.push_back(week);
            // clear week vector
            week.clear();
        }
        w -= 1;
    }
    for (int t = 1; t <= daysInMonth; t++) {
        z += 1;
        stringstream s;
        s << setw(3) << t;
        week.push_back(s.str());
        if ((z % 7) == 0) {
            weekScheme.push_back(week);
            // clear week vector
            week.clear();
        }
    }
    // write trailing spaces
    while (z < 42) {
        z += 1;
        week.push_back(spaces);
        if ((z % 7) == 0) {
            weekScheme.push_back(week);
            // clear week vector
            week.clear();
        }
    }
}
