# GTK-Calendar-Sheet
Calendar Sheet including German holidays with creating of ICS files ( C++ / Linux / Gnome / GTK / gtkmm ) 

See the calendar for a given year, including all German holidays and put the dates into your personal calendar
(printing of a calendar sheet is possible)

The program was written in C++ with use of gtkmm wrapper for Gnome GTK environment of Linux.

The development environment in the moment is Netbeans IDE 8.2 under Fedora 28 Cinnamon. Alternatively you can easily compile and run the program in Terminal with the added shell script:

$ sh ./GTKCalendarSheet.sh

I added an earlier command line version in FORTRAN without output of german holidays. This is easily compiled (assumed the fortran package for gcc is installed) with

$ gfortran -o kalenda kalenda.f90

The program follows the design of an earlier (unpublished) program CalendarSheet written in Swift. Since I switched from macOS to Fedora Linux (for what reasons ever) I had to change my programming language. For "simplicity" I choose C++ and to my pleasure found its "way to think" very similar to Swift and Objective-C. In some aspects I found C++ in combination with GTK easier compared to Swift ... Furthermore with the gtkmm wrapper you have an excellent tool for developing own programs.

I wrote this program to become familiar with the C++ language, especially the GTK-API under the gtkmm wrapper and to get a feeling how to display textviews on the screen. Take it as example for handling of a window, menu, toolbar, integrating an AboutDialog and printing the content of textviews. Besides that you get information about calendars and dates. Since modern Smartphones have all the functions built-in to remember the national holidays, my program nowadays is relatively useless ... but ... you can learn a lot about calendars (julian, gregorian, ecclesiastic) plus calculation of the easter date with all of its arduousness and complexity.

Usage: You will find the program mostly self explaining. On input of a year number greater than 1583 a calendar sheet including the dates for German holidays are calculated. By clicking on "Speichern..." you have the possibilty to save the dates of the holidays in a calendar file with the extension .ics, which will be accepted by calendar programs on PC or mobile phones. Thereby you are able to view the holidays on your personal calendar. Quit the program with "Beenden". In addition you will find a menu and a tool bar which will allow you to print the sheet on an external printer or into a file (see the included pdf example). Preview before printing is possible. To be honest, these routines are adopted with slight modifications from the GTKmm documentation. As a gimmick you will learn how to output the special days of the calendar in a different font, weight or color, both in the textview and in printing. I chose to display these days in bold and red ...

The possibility to display the german holidays in form of a tableview is commented out ... you can restore this option easily.

There is an in my eyes excellent article from Howart Hinnant
<http://howardhinnant.github.io/date_algorithms.html>
regarding calculating and converting gregorian dates. I modified some of his routines in an own class Gregorian which assigns every day in the gregorian calendar an unique number. In my implementation this number is defined as double. If this number has decimal places these are interpreted as fraction of the day which means if you multiply this fraction with 86400 (24x60x60) you will get the seconds elapsed after midnight. From that it is easy to calculate the time in hours, minutes and seconds ...

Disclaimer: Use the program for what purpose you like, but hold in mind, that I will not be responsible for any harm it will cause to your hard- or software. It was your decision to use this piece of software.

