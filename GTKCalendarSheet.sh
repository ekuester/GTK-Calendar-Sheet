g++ `pkg-config gtkmm-3.0 --cflags --libs` -c main.cpp calendarsheetwindow.cpp gregorian.cpp holiday.cpp month.cpp printformoperation.cpp
g++ main.o calendarsheetwindow.o gregorian.o holiday.o month.o printformoperation.o -o GTKCalendarSheet `pkg-config gtkmm-3.0 --cflags --libs`
./GTKCalendarSheet

