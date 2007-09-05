#include "MenuBar.h"

MenuBar::MenuBar() {
	this->append(*new Gtk::MenuItem("File"));
	this->append(*new Gtk::MenuItem("Edit", true));
}
