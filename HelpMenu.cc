#include "HelpMenu.h"

HelpMenu::HelpMenu(Gtk::Window *main_win) {
	Gtk::Menu *help_content_menu = new Gtk::Menu();
	help_content_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::HELP));
	help_content_menu->items().push_back(Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::ABOUT));

	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_Help", *help_content_menu));
}
