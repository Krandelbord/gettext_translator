#include "MenuBar.h"

MenuBar::MenuBar() {
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_File", *this->createFileMenu()));
	this->append(*new Gtk::MenuItem("Edit", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::OPEN,  sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	file_menu->items().push_back( Gtk::Menu_Helpers::MenuElem("Cokolwiek", sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	return file_menu;
}

void MenuBar::onQuitMenuitem() {
	Gtk::Main::quit();
}

void MenuBar::onOpenMenuitem() {
	
}
