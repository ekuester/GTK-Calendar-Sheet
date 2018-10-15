//
//  File: calendarsheetwindow.h
//  Calendar Sheet
//
//  Created by Erich Küster on January 28, 2016
//  Renewed for C++ on September 9, 2018
//  Copyright © 2016 Erich Kuester. All rights reserved.
//

#ifndef CALENDARSHEETWINDOW_H
#define CALENDARSHEETWINDOW_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include "gregorian.h"
#include "holiday.h"
#include "month.h"
#include "printformoperation.h"

using namespace std;

class Gregorian;
class Holiday;
class Month;
class PrintFormOperation;

class CalendarSheetWindow : public Gtk::Window {
public:
    CalendarSheetWindow(const Glib::RefPtr<Gtk::Application>& app);
    virtual ~CalendarSheetWindow();

    Glib::ustring calendar = "";
    guint yearNumber = 0;
    std::vector<Holiday*> holidays;
    std::vector<Month*> months;

protected:
    std::vector<Glib::ustring> normal_tag_names = {
        "liber_mono",
        "not_editable"
    };
    std::vector<Glib::ustring> bold_tag_names = {
        "liber_mono_bold",
        "red_foreground",
        "not_editable"
    };

    string bigDigits(int value);
    Gtk::TextBuffer::iterator
        fill_textbuffer(Gtk::TextBuffer::iterator iter, string text, std::vector<Glib::ustring> tag_names);

    void germanHolidays();
    guint get_yearnumber();

    void build_main_menu(const Glib::RefPtr<Gtk::Application>& app);
    void print_or_preview(Gtk::PrintOperationAction print_action);

    //Signal handlers for entry and buttons
    void on_activated();
    void on_action_quit();
    void save_holidays_clicked(guint* year);
    //Signal handlers for menu actions
    void on_menu_file_new();
    void on_menu_file_page_setup();
    void on_menu_file_print_preview();
    void on_menu_file_print();
    void on_menu_file_quit();
    void on_menu_help_about();
     //Signal handler for AboutDialog
    void on_about_dialog_response(int response_id);
    //Signal handlers for print operation
    //We handle these so can get necessary information to update the UI or print settings.
    //Our derived PrintOperation class also overrides some default signal handlers.
    void on_printoperation_status_changed();
    void on_printoperation_done(Gtk::PrintOperationResult result);
/*
    //Three model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:

        ModelColumns() {
            add(m_col_id);
            add(m_name_string);
            add(m_date_string);
        }

        Gtk::TreeModelColumn<guint> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_name_string;
        Gtk::TreeModelColumn<Glib::ustring> m_date_string;
    };
    ModelColumns m_Columns; */

    //Printing-related objects:
    Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
    Glib::RefPtr<Gtk::PrintSettings> m_refSettings;
    Glib::RefPtr<PrintFormOperation> m_refPrintFormOperation;

    // Child widgets
    Gtk::MenuBar m_MenuBar;
    Gtk::MenuItem m_MenuFile;
    Gtk::Menu s_MenuFile;
    Gtk::ImageMenuItem s_MenuItemNew;
    Gtk::ImageMenuItem s_MenuItemPageSetup;
    Gtk::ImageMenuItem s_MenuItemPrintPreview;
    Gtk::ImageMenuItem s_MenuItemPrint;
    Gtk::SeparatorMenuItem s_MenuItemLine;
    Gtk::ImageMenuItem s_MenuItemQuit;
    Gtk::MenuItem m_MenuHelp;
    Gtk::Menu s_MenuHelp;
    Gtk::ImageMenuItem s_MenuItemAbout;
    Gtk::Toolbar t_Toolbar;
    Gtk::ToolButton t_ToolButtonNew;
    Gtk::ToolButton t_ToolButtonPrintPreview;
    Gtk::SeparatorToolItem t_ToolItemSpace;
    Gtk::ToolButton t_ToolButtonPrint;

    Gtk::Box m_HBoxTop;
    Gtk::Label m_Label;
    Gtk::Entry m_Text;

    Gtk::Box m_VBox;
//    Gtk::ScrolledWindow m_TableWindow;
//    Gtk::TreeView m_TreeView;
//    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    Gtk::Frame m_TextFrame;
    Gtk::ScrolledWindow m_TextWindow;
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
    Gtk::AboutDialog m_Dialog;

    Glib::RefPtr<Gtk::Builder> m_refBuilder;

    Gtk::Box m_HBoxBottom;
    Gtk::ButtonBox m_SaveButtonBox;
    Gtk::Button m_ButtonSave;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_ButtonQuit;
    Gtk::Frame m_StatusFrame;
    unsigned m_ContextId;
    Gtk::Statusbar m_Statusbar;
};

#endif /* CALENDARSHEETWINDOW_H */
