/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kuestere
 *
 * Created on 9. September 2018, 18:10
 */

#include <gtkmm/application.h>
#include "calendarsheetwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.kuester.application");

    CalendarSheetWindow window(app);

    //Shows the window and returns when it is closed.
    return app->run(window);
}
