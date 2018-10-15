//
//  File:   calendarsheetwindow.cpp
//  Calendar Sheet
//
//  Created by Erich Küster on January 28, 2016
//  Renewed for C++ on September 9, 2018
//  Copyright © 2016 Erich Kuester. All rights reserved.
//

#include "calendarsheetwindow.h"
#include "about.xpm"

using namespace std;

const Glib::ustring app_title = "Gtk+: Application - Calendar Sheet with German Holidays";

CalendarSheetWindow::CalendarSheetWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_HBoxTop(Gtk::ORIENTATION_HORIZONTAL),
  m_MenuBar(),
  s_MenuFile(),
  s_MenuItemNew(Gtk::Stock::NEW),
  s_MenuItemPageSetup(Gtk::Stock::PAGE_SETUP),
  s_MenuItemPrintPreview(Gtk::Stock::PRINT_PREVIEW),
  s_MenuItemPrint(Gtk::Stock::PRINT),
  s_MenuItemLine(),
  s_MenuItemQuit(Gtk::Stock::QUIT),
  s_MenuItemAbout(Gtk::Stock::ABOUT),
  s_MenuHelp(),
  t_Toolbar(),
  t_ToolButtonNew(Gtk::Stock::NEW),
  t_ToolItemSpace(),
  t_ToolButtonPrintPreview(Gtk::Stock::PRINT_PREVIEW),
  t_ToolButtonPrint(Gtk::Stock::PRINT),
  m_Label(),
  m_Text(),
  //m_TableWindow(),
  m_TextFrame(),
  m_TextWindow(),
  m_HBoxBottom(Gtk::ORIENTATION_HORIZONTAL),
  m_SaveButtonBox(Gtk::ORIENTATION_HORIZONTAL),
  m_ButtonSave("Speichern...", true),
  m_ButtonBox(Gtk::ORIENTATION_HORIZONTAL),
  m_ButtonQuit("Beenden", true),
  m_StatusFrame(),
  m_Dialog(),
  m_Statusbar()
{
    m_refPageSetup = Gtk::PageSetup::create();
    m_refSettings = Gtk::PrintSettings::create();

    m_ContextId = m_Statusbar.get_context_id(app_title);
    
    set_title(app_title);
    set_border_width(5);
    set_default_size(640, 640);

    add(m_VBox);
    // add menu structure
//    build_main_menu(app);
    // menu "File"
    m_MenuFile = Gtk::MenuItem("Datei");
    s_MenuItemNew.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_new));
    s_MenuItemPageSetup.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_page_setup));
    s_MenuItemPrintPreview.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_print_preview));
    s_MenuItemPrint.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_print));
    s_MenuItemQuit.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_action_quit));
    s_MenuFile.append(s_MenuItemNew);
    s_MenuFile.append(s_MenuItemPageSetup);
    s_MenuFile.append(s_MenuItemPrintPreview);
    s_MenuFile.append(s_MenuItemPrint);
    s_MenuFile.append(s_MenuItemLine);
    s_MenuFile.append(s_MenuItemQuit);
    m_MenuFile.set_submenu(s_MenuFile);
    // menu "Help"
    m_MenuHelp = Gtk::MenuItem("Hilfe");
    s_MenuItemAbout.signal_activate().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_help_about));
    s_MenuHelp.append(s_MenuItemAbout);
    m_MenuHelp.set_submenu(s_MenuHelp);
    // set menu bar
    m_MenuBar.append(m_MenuFile);
    m_MenuBar.append(m_MenuHelp);
    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);
    t_Toolbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);
    t_ToolButtonNew.set_tooltip_text("Neu");
    t_ToolButtonNew.signal_clicked().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_new));
    t_ToolButtonPrintPreview.set_tooltip_text("Druckvorschau...");
    t_ToolButtonPrintPreview.signal_clicked().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_print_preview));
    t_ToolButtonPrint.set_tooltip_text("Drucken...");
    t_ToolButtonPrint.signal_clicked().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_menu_file_print));
    t_Toolbar.append(t_ToolButtonNew);
    t_Toolbar.append(t_ToolItemSpace);
    t_Toolbar.append(t_ToolButtonPrintPreview);
    t_Toolbar.append(t_ToolButtonPrint);
    m_VBox.pack_start(t_Toolbar, Gtk::PACK_SHRINK);

    // fill vertical box
    m_Label.set_markup("<b>Jahreszahl eingeben:</b>");
    m_Label.set_vexpand(false);
    m_Label.set_hexpand(false);
    m_Label.set_halign(Gtk::ALIGN_START);
    m_Text.set_vexpand(false);
    m_Text.set_hexpand(false);
    m_Text.set_halign(Gtk::ALIGN_END);
    m_Text.set_text("2018");
    // Label, then TextEntry left to right in horizontal row
    m_HBoxTop.pack_start(m_Label, Gtk::PACK_SHRINK, 16);
    m_HBoxTop.pack_start(m_Text, Gtk::PACK_SHRINK);
    m_Text.signal_activate().connect(sigc::mem_fun(*this, &CalendarSheetWindow::on_activated));
//    m_Text.signal_changed().connect(sigc::mem_fun(*this, &CalendarSheetWindow::on_entry_insert));
    m_VBox.pack_start(m_HBoxTop, Gtk::PACK_SHRINK);

    //Create the Text Buffer
    m_refTextBuffer = Gtk::TextBuffer::create();
    //m_refTextBuffer->create_tag("monospace")->property_family() = "monospace";
    m_refTextBuffer->create_tag("italic")->property_style() = Pango::Style::STYLE_ITALIC;
    m_refTextBuffer->create_tag("bold")->property_weight() = Pango::Weight::WEIGHT_BOLD;
    m_refTextBuffer->create_tag("liber_mono")->property_font() = "Liberation Mono Regular 10";
    m_refTextBuffer->create_tag("liber_mono_bold")->property_font() = "Liberation Mono Bold 10";
    m_refTextBuffer->create_tag("blue_foreground")->property_foreground() = "blue";
    m_refTextBuffer->create_tag("red_foreground")->property_foreground() = "red";
    m_refTextBuffer->create_tag("not_editable")->property_editable() = FALSE;
    m_TextView.set_buffer(m_refTextBuffer);
    m_TextView.set_wrap_mode(Gtk::WRAP_WORD);

/*
    // Add the TreeView, inside a ScrolledWindow
    m_TableWindow.add(m_TreeView);
    // Only show the scrollbars when they are necessary:
    m_TableWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_VBox.pack_start(m_TableWindow);
    m_VBox.set_border_width(8); */

    //Add the TextView, inside a ScrolledWindow
//    m_TextWindow.set_size_request(-1, 60);
    m_TextFrame.add(m_TextView);
    m_TextWindow.add(m_TextFrame);

    //Only show the scrollbars when they are necessary:
    m_TextWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_VBox.pack_start(m_TextWindow, Gtk::PACK_EXPAND_WIDGET);
    m_VBox.set_border_width(8);

    // two buttons underneath
    // SaveButtonBox to the left end of vertical Box
    m_HBoxBottom.pack_start(m_SaveButtonBox, Gtk::PACK_SHRINK);
    m_SaveButtonBox.pack_start(m_ButtonSave, Gtk::PACK_SHRINK);
    m_SaveButtonBox.set_border_width(2);
    m_SaveButtonBox.set_layout(Gtk::BUTTONBOX_START);
    // transfer argument to signal routine
    gpointer yearPtr = GUINT_TO_POINTER(yearNumber);
    m_ButtonSave.signal_clicked().connect(sigc::bind<guint*>(sigc::mem_fun(*this,
        &CalendarSheetWindow::save_holidays_clicked), &yearNumber));
    // ButtonBox to the right end of vertical box
    m_HBoxBottom.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);
    m_HBoxBottom.set_border_width(8);
    m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
    m_ButtonBox.set_border_width(2);
    m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
    m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
            &CalendarSheetWindow::on_action_quit));
    m_VBox.pack_start(m_HBoxBottom, Gtk::PACK_SHRINK);
/*
    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Add the TreeView's view columns:
    //This number will be shown with the default numeric formatting.
    m_TreeView.append_column("ID", m_Columns.m_col_id);
    m_TreeView.append_column("Name des Feiertags", m_Columns.m_name_string);
    m_TreeView.append_column("Datum des Feiertags", m_Columns.m_date_string);

    //Make all the columns reorderable and resizable:
    //This is not necessary, but it's nice to show the feature.
    //You can use TreeView::set_column_drag_function() to more
    //finely control column drag and drop.
    for ( auto* column : m_TreeView.get_columns() ) {
        column->set_reorderable();
        column->set_resizable(true);
        //column->set_alignment(Gtk::ALIGN_FILL);
    }
 */
    m_StatusFrame.add(m_Statusbar);
    m_VBox.pack_start(m_StatusFrame, Gtk::PACK_SHRINK);
    m_ContextId = m_Statusbar.push("Bereit", m_ContextId);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(app_title);
    m_Dialog.set_version("Version 1.2.5");
    m_Dialog.set_copyright("Copyright © 2018 Erich Küster. All rights reserved.");
    m_Dialog.set_comments("Calendar Sheet with German Holidays");
    std::ifstream licenseFile("LICENSE");
    std::stringstream licenseStream;
    licenseStream << licenseFile.rdbuf();
    m_Dialog.set_license(licenseStream.str());
    std::ifstream commentsFile("COMMENTS");
    std::stringstream commentsStream;
    commentsStream << commentsFile.rdbuf();
    m_Dialog.set_comments(commentsStream.str());

    m_Dialog.set_website("http://www.gtkmm.org");
    m_Dialog.set_website_label("gtkmm Website - C++ Interfaces for GTK+ and GNOME");

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Erich Küster, Krefeld/Germany");
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(
        sigc::mem_fun(*this, &CalendarSheetWindow::on_about_dialog_response));

    show_all_children();
}

CalendarSheetWindow::~CalendarSheetWindow() {
    Gregorian logout = Gregorian();
    cout << "closing Calendar Sheet Window: " << logout.formatTimeShort() << endl;
}

// evaluate german holidays
void CalendarSheetWindow::germanHolidays() {
    Glib::ustring fixNames[12] = {
        "Neujahr",
        "Heilige Drei Könige",
        "Valentinstag",
        "Walpurgisnacht",
        "Tag der Arbeit",
        "Mariä Himmelfahrt",
        "Allerheiligen",
        "Allerseelen",
        "Heiligabend",
        "1. Weihnachtstag",
        "2. Weihnachtstag",
        "Sylvester"
    };
    std::vector<std::pair<unsigned, unsigned> > fixDates = {
        { 1,  1},
        { 6,  1},
        {14,  2},
        {30,  4},
        { 1,  5},
        {15,  8},
        { 1, 11},
        { 2, 11},
        {24, 12},
        {25, 12},
        {26, 12},
        {31, 12}
    };
    int i = 0;
    for ( auto fixDate : fixDates ) {
        unsigned d = fixDate.first;
        unsigned m = fixDate.second;
        Gregorian fixDay = Gregorian(yearNumber, m, d);
        Holiday *fixHoliday = new Holiday(fixDay, fixNames[i]);
        holidays.push_back(fixHoliday);
        i++;
    }
    // easter is first Sunday after the ecclesiastical full moon
    // occurring on or soonest after March 21
    Holiday* easter = new Holiday(0, yearNumber, "Ostern");
    holidays.push_back(easter);
    std::vector<std::pair<Glib::ustring, int> > easterDates = {
        {"Altweiberfastnacht", -52},
        {"Rosenmontag", -48},
        {"Fastnacht", -47},
        {"Aschermittwoch", -46},
        {"Karfreitag", -2},
        {"Ostermontag", 1},
        {"Christi Himmelfahrt", 39},
        {"Pfingsten", 49},
        {"Pfingstmontag", 50},
        {"Fronleichnam", 60}
    };
    for ( auto easterDate : easterDates ) {
        Gregorian easterRelative = Gregorian(easter->numberOfDay + easterDate.second);
        Holiday* easterHoliday = new Holiday(easterRelative, easterDate.first);
        holidays.push_back(easterHoliday);
    }
    // since 1923 mother's day is on second sunday in may
    if (yearNumber > 1923) {
        Holiday* mothersDay = new Holiday(1, yearNumber, "Muttertag");
        holidays.push_back(mothersDay);
    }
    // since 1953 there is a unity day in Germany
    if (yearNumber > 1953) {
        // Tag der d(D)eutschen Einheit
        // Im Jahr 1990 gab es beide Tage ( 17. Juni und 3. Oktober )
        if (yearNumber < 1991) {
            Gregorian unityNumber = Gregorian(yearNumber, 6, 17);
            Glib::ustring unityName = "Tag der deutschen Einheit";
            Holiday* unityDay = new Holiday(unityNumber, unityName);
            holidays.push_back(unityDay);
        }
        if (yearNumber > 1989) {
            Gregorian unityNumber = Gregorian(yearNumber, 10, 3);
            Glib::ustring unityName = "Tag der Deutschen Einheit";
            Holiday* unityDay = new Holiday(unityNumber, unityName);
            holidays.push_back(unityDay);            
        }
    }
    // deads' sunday is last sunday in november before first sunday in advent
    Holiday* deadsSunday = new Holiday(2, yearNumber, "Totensonntag");
    holidays.push_back(deadsSunday);
    std::vector<std::pair<Glib::ustring, int> > novemberDates = {
        {"Volkstrauertag", -7},
        {"Buß- und Bettag", -4},
        {"1. Advent", 7}
    };
    for ( auto novemberDate : novemberDates ) {
        Gregorian novemberRelative = Gregorian(deadsSunday->numberOfDay + novemberDate.second);
        Holiday* novemberHoliday = new Holiday(novemberRelative, novemberDate.first);
        holidays.push_back(novemberHoliday);
    }
    std::sort(holidays.begin(), holidays.end(), [](const Holiday* h1, const Holiday* h2){
        return h1->numberOfDay < h2->numberOfDay;});
    stringstream infoStream;
    infoStream << holidays.size() << " Feiertage für das Jahr " << yearNumber << " gespeichert";
    m_ContextId = m_Statusbar.push(infoStream.str(), m_ContextId);
}

Gtk::TextBuffer::iterator CalendarSheetWindow::fill_textbuffer(
    Gtk::TextBuffer::iterator iter, string text, std::vector<Glib::ustring> tag_names) {
    return m_refTextBuffer->insert_with_tags_by_name(iter, text, tag_names);
}

// read yearnumber from entry
guint CalendarSheetWindow::get_yearnumber() {
    guint year = 0;
    // This code converts from string to number safely.
    stringstream numberStream(m_Text.get_text());
    if (numberStream >> year) {
        if ((year < 1583) || (year > 2399)) {
            Gtk::MessageDialog dialog(*this,
                    "Error: Check input",
                    false,
                    Gtk::MESSAGE_ERROR,
                    Gtk::BUTTONS_OK, // Gtk::BUTTONS_OK, Gtk::BUTTONS_NONE,
                    true);
            dialog.set_secondary_text(
                    "Year should be between 1583 and 2399");
            int result = dialog.run();
            return 0;
        }
        return year;
    }
    cout << "Invalid number, please try again" << endl;
    return 0;
}

// handles enter pressed
void CalendarSheetWindow::on_activated() {
    int year = get_yearnumber();
    if (year) {
        // valid number for year otherwise ignore input
        if (year != yearNumber) {
            // new evaluation necessary
            if (holidays.size() > 0) {
                months.clear();
                holidays.clear();
                //m_refTreeModel->clear();
                Gtk::TextBuffer::iterator iter_begin = 
                    m_refTextBuffer->get_iter_at_offset(0);
                Gtk::TextBuffer::iterator iter_end = 
                    m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
                m_refTextBuffer->erase(iter_begin, iter_end);
            }
            yearNumber = year;
            // fill holidays vector
            germanHolidays();
            // fill months vector
            for (int m = 1; m <= 12; m++) {
                Gregorian firstDay = Gregorian(yearNumber, m, 1);
                Month* monat = new Month(&firstDay);
                months.push_back(monat);
            }
            // add holidays to months vector
            for (auto* holiday : holidays) {
                int m = std::get<1>(holiday->numberOfDay.yeardate); // 1 ... 12
                auto d = std::get<2>(holiday->numberOfDay.yeardate); // 1 ... 31
                auto o = holiday->numberOfDay.weekday();
                auto month = months[m-1];
                auto l = month->firstWeekday; // 0 ... 6
                if (o != 6) {
                    int index = l + d;
                    int w = index / 7; // week 0 ... 6
                    int p = index - w * 7 - 1; // weekday ordinal in week
                    month->weekScheme[w][p].resize(4, 'r'); // mark holiday with 'r'
                }
            }
/* 
            // Fill the TreeView's model
            // Add table row for every holiday object
            int i = 1;
            for (auto* holiday : holidays) {
                Gtk::TreeModel::Row row = *(m_refTreeModel->append());
                row[m_Columns.m_col_id] = i++;
                row[m_Columns.m_name_string] = holiday->nameOfDay;
                row[m_Columns.m_date_string] = holiday->numberOfDay.formatDateLong();
            } */

            // fill simultaneously a normal text buffer and a markup text buffer
            stringstream calendarStream;
            Gtk::TextBuffer::iterator iter;
            Gtk::TextBuffer::iterator iter_end = 
                m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
            stringstream preamble;
            preamble << "A happy new year ..." << endl;
            preamble << bigDigits(yearNumber);
            iter = fill_textbuffer(iter_end, preamble.str(), normal_tag_names);
            calendarStream << preamble.str();
            for (int j = 0; j < 4; j++) {
                stringstream nameStream;
                stringstream dayStream;
                for (int m = j*3; m < j*3+3; m++) {
                    auto size = months[m]->nameOfMonth.size();
                    //string padding(22 - months[k]->nameOfMonth.size(), ' ');
                    nameStream << months[m]->nameOfMonth << setw(22 - size) << " ";
                    dayStream << " Mo Di Mi Do Fr Sa So ";
                }
                nameStream << endl;
                calendarStream << nameStream.str();
                iter = fill_textbuffer(iter, nameStream.str(), normal_tag_names);
                dayStream << endl;
                calendarStream << dayStream.str();
                iter = fill_textbuffer(iter, dayStream.str(), normal_tag_names);
                for (int w = 0; w < 6; w++) {
                    for (int m = j*3; m < j*3+3; m++) {
                        int p = 0;
                        while (p < 6) {
                            string day = months[m]->weekScheme[w][p];
                            if (day.size() < 4) {
                                calendarStream << day;
                                iter = fill_textbuffer(iter, day, normal_tag_names);
                            } else {
                                day.resize(3);
                                calendarStream << "<span foreground=\"red\"><b>"
                                    << day << "</b></span>";
                                iter = fill_textbuffer(iter, day, bold_tag_names);
                            }
                            p++;
                        }
                        calendarStream << "<span foreground=\"red\"><b>"
                            << months[m]->weekScheme[w][p] << "</b></span> ";
                        iter = fill_textbuffer(iter, months[m]->weekScheme[w][p], bold_tag_names);
                        iter = fill_textbuffer(iter, " ", normal_tag_names);
                    }
                    calendarStream << endl;
                    iter = fill_textbuffer(iter, "\n", normal_tag_names);
                }
            }
            stringstream postamble;
            string hope = "let's hope it's a good one";
            string fear = "without any fear";
            postamble << setw(40) << " " << hope << endl << setw(50) << " " << fear << endl;
            iter = fill_textbuffer(iter, postamble.str(), normal_tag_names);
            calendarStream << postamble.str();
            stringstream holidayStream;
            holidayStream << "Feiertage:" << endl;
            for (auto* holiday : holidays) {
                auto size = holiday->nameOfDay.size();
                holidayStream << holiday->nameOfDay
                    << setw(30 - size) << " " << holiday->numberOfDay.formatDateLong() << endl;
            }
            iter = fill_textbuffer(iter, holidayStream.str(), normal_tag_names);
            calendarStream << holidayStream.str();
            calendar = calendarStream.str();
        }
    }
}

void CalendarSheetWindow::on_action_quit() {
    hide();
}

void CalendarSheetWindow::on_menu_help_about() {
    m_Dialog.show();
    //bring it to the front, in case it was already shown:
    m_Dialog.present();
}

void CalendarSheetWindow::on_about_dialog_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            m_Dialog.hide();
            break;
        default:
            std::cout << "Unerwartete Antwort!" << std::endl;
            break;
    }
}

void CalendarSheetWindow::save_holidays_clicked(guint* year) {
    Glib::ustring info;
    if (*year > 0) {
        const char* dateFormat = "%Y%m%dT%H%M%SZ";
        // prepare timestamp
        time_t time_now = time(0);
        stringstream timeStream;
        timeStream << put_time(localtime(&time_now), dateFormat);
        string timeStamp = timeStream.str();
        stringstream filename;
        filename << "Holidays-" << *year << ".ics";
        // cout << filename.str() << endl;
        ofstream calendarFile;
        calendarFile.open(filename.str());
        calendarFile << "BEGIN:VCALENDAR\n";
        calendarFile << "METHOD:PUBLISH\n";
        calendarFile << "VERSION:2.0\n";
        calendarFile << "X-WR-CALNAME:Feiertage\n";
        calendarFile << "PRODID:-//Apple Inc.//iCal 5.0.0//DE\n";
        int i = 1;
        // loop through holidays in year
        for ( auto* holiday : holidays) {
            calendarFile << "BEGIN:VEVENT\n";
            calendarFile << "CREATED: " << timeStamp << "\n";
            // add-on "-kuester-" can be changed at will
            calendarFile << "UID:" << timeStamp << "@kuester-" << i << "\n";
            calendarFile << "SUMMARY: " << holiday->nameOfDay << "\n";
            calendarFile << "DESCRIPTION:Feiertage\n";
            calendarFile << "X-MOZILLA-ALARM-DEFAULT-LENGTH:0\n";
            calendarFile << "X-MOZILLA-RECUR-DEFAULT-UNITS:0\n";
            calendarFile << "RRULE:0\n";
            calendarFile << "TRANSP:TRANSPARENT\n";
            calendarFile << "DTSTART;VALUE=DATE:"
                    << holiday->numberOfDay.formatDateShort() << "\n";
            Gregorian nextNumber = holiday->numberOfDay + 1;
            calendarFile << "DTEND;VALUE=DATE:"
                    << nextNumber.formatDateShort() << "\n";
            calendarFile << "DTSTAMP:" << timeStamp << "\n";
            calendarFile << "LAST-MODIFIED:" << timeStamp << "\n";
            calendarFile << "END:VEVENT\n";
            i++;
        }
        calendarFile << "END:VCALENDAR\n";
        calendarFile.close();
        stringstream infoStream;
        infoStream << holidays.size() << " Feiertage für Jahr " << *year << " gespeichert";
        info = infoStream.str();
        timeStream.clear();
    } else {
        info = "No data for calendar available";
    }
    m_ContextId = m_Statusbar.push(info, m_ContextId);
}

string CalendarSheetWindow::bigDigits(int value) {
    std::vector<std::vector<string>> nineSegments = {
        {   " 000000 ",
            "00    00",
            "00    00",
            "00    00",
            "00    00",
            "00    00",
            "00    00",
            "00    00",
            " 000000 "},
        {   "   11   ",
            "  111   ",
            "   11   ",
            "   11   ",
            "   11   ",
            "   11   ",
            "   11   ",
            "   11   ",
            "11111111"},
        {   " 222222 ",
            "22    22",
            "      22",
            "   2222 ",
            "  22    ",
            " 22     ",
            "22      ",
            "22      ",
            "22222222"},
        {   " 333333 ",
            "33    33",
            "      33",
            "   3333 ",
            "      33",
            "      33",
            "      33",
            "33    33",
            " 333333 "},
        {"     44 ",
            "    444 ",
            "   4444 ",
            "  44 44 ",
            " 44  44 ",
            "44444444",
            "     44 ",
            "     44 ",
            "     44 "},
        {   " 555555 ",
            "55      ",
            "55      ",
            "5555555 ",
            "      55",
            "      55",
            "      55",
            "55    55",
            " 555555 "},
        {   " 666666 ",
            "66    66",
            "66      ",
            "6666666 ",
            "66    66",
            "66    66",
            "66    66",
            "66    66",
            " 666666 "},
        {   "77777777",
            "     77 ",
            "    77  ",
            "   77   ",
            "   77   ",
            "   77   ",
            "   77   ",
            "   77   ",
            "   77   "},
        {   " 888888 ",
            "88    88",
            "88    88",
            " 888888 ",
            "88    88",
            "88    88",
            "88    88",
            "88    88",
            " 888888 "},
        {   " 999999 ",
            "99    99",
            "99    99",
            "99    99",
            " 9999999",
            "      99",
            "      99",
            "99    99",
            " 999999 "}
    };

    string scheme = "";
    // maximum 8 digits
    int digits = value;
    string padding(10, ' ');
    int stellen[10] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    while (digits != 0) {
        stellen[i] = digits % 10;
        digits /= 10;
        i += 1;
    }
    for (int j = 0; j < 9; j++) {
        int k = i;
        scheme = scheme + padding;
        while (k != 0) {
            k -= 1;
            scheme = scheme + "  " + nineSegments[stellen[k]][j];
        }
        scheme = scheme + "\n";
    }
    return scheme;
}

void CalendarSheetWindow::on_printoperation_status_changed()
{
  Glib::ustring status_msg;

  if (m_refPrintFormOperation->is_finished())
  {
    status_msg = "Print job completed.";
  }
  else
  {
    //You could also use get_status().
    status_msg = m_refPrintFormOperation->get_status_string();
  }

  m_ContextId = m_Statusbar.push(status_msg, m_ContextId);
}

void CalendarSheetWindow::on_printoperation_done(Gtk::PrintOperationResult result)
{
  //Printing is "done" when the print data is spooled.

  if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
  {
    Gtk::MessageDialog err_dialog(*this, "Error printing form", false,
            Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    err_dialog.run();
  }
  else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
  {
    //Update PrintSettings with the ones used in this PrintOperation:
    m_refSettings = m_refPrintFormOperation->get_print_settings();
  }

  if (!m_refPrintFormOperation->is_finished())
  {
    //We will connect to the status-changed signal to track status
    //and update a status bar. In addition, you can, for example,
    //keep a list of active print operations, or provide a progress dialog.
    m_refPrintFormOperation->signal_status_changed().connect(sigc::mem_fun(*this,
        &CalendarSheetWindow::on_printoperation_status_changed));
  }
}

void CalendarSheetWindow::print_or_preview(Gtk::PrintOperationAction print_action) {
    //Create a new PrintOperation with our PageSetup and PrintSettings:
    //(We use our derived PrintOperation class)
    m_refPrintFormOperation = PrintFormOperation::create();

//    m_refPrintFormOperation->set_name(m_NameEntry.get_text() + " " + m_SurnameEntry.get_text());
    // Don't include hidden objects
//    m_refPrintFormOperation->set_calendar(m_refTextBuffer->get_text(false));
    m_refPrintFormOperation->set_calendar(calendar);
    // In the printing/advanced example, the font will be set through a custom tab
    // in the print dialog.

    m_refPrintFormOperation->set_track_print_status();
    m_refPrintFormOperation->set_default_page_setup(m_refPageSetup);
    m_refPrintFormOperation->set_print_settings(m_refSettings);

    m_refPrintFormOperation->signal_done().connect(sigc::mem_fun(*this,
            &CalendarSheetWindow::on_printoperation_done));
    try {
        m_refPrintFormOperation->run(print_action /* print or preview */, *this);
    } catch (const Gtk::PrintError& ex) {
        //See documentation for exact Gtk::PrintError error codes.
        std::cerr << "An error occurred while trying to run a print operation:"
            << ex.what() << std::endl;
    }
}

void CalendarSheetWindow::on_menu_file_new() {
    m_Text.set_text(Glib::ustring());
    Gtk::TextBuffer::iterator iter_begin = 
        m_refTextBuffer->get_iter_at_offset(0);
    Gtk::TextBuffer::iterator iter_end = 
        m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
    m_refTextBuffer->erase(iter_begin, iter_end);
}

void CalendarSheetWindow::on_menu_file_page_setup() {
    //Show the page setup dialog, asking it to start with the existing settings:
    auto new_page_setup =
        Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);

    //Save the chosen page setup dialog for use when printing, previewing, or
    //showing the page setup dialog again:
    m_refPageSetup = new_page_setup;
}

void CalendarSheetWindow::on_menu_file_print_preview() {
    print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void CalendarSheetWindow::on_menu_file_print() {
    print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}

void CalendarSheetWindow::on_menu_file_quit() {
    hide();
}
