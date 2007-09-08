#include "DictionariesMenu.h"

DictionariesMenu::DictionariesMenu() {
	this->items().push_back( Gtk::Menu_Helpers::MenuElem("First dictionary"));
	this->items().push_back( Gtk::Menu_Helpers::MenuElem("Second dictionary"));
	this->items().push_back( Gtk::Menu_Helpers::MenuElem("Third dictionary"));
}
