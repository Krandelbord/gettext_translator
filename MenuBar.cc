#include "MenuBar.h"

MenuBar::MenuBar(Gtk::Window &main_win) {
	m_main_win = &main_win;
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_File", *this->createFileMenu()));
	this->append(*new Gtk::MenuItem("Edit", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::OPEN,  sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	file_menu->items().push_back( Gtk::Menu_Helpers::MenuElem("Cokolwiek", sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	return file_menu;
}

void MenuBar::onQuitMenuitem() {
	Gtk::Main::quit();
}

void MenuBar::onOpenMenuitem() {
	Gtk::FileChooserDialog fc_dialog(*m_main_win, "open file");
	fc_dialog.run();
}
