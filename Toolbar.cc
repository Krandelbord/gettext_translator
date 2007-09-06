#include "Toolbar.h"

Toolbar::Toolbar() {
	this->set_tooltips();

	this->append(*new Gtk::ToolButton(Gtk::Stock::OPEN));
	this->append(*new Gtk::ToolButton(Gtk::Stock::SAVE));

	this->append(*new Gtk::ToolButton(Gtk::Stock::COPY));
	this->append(*new Gtk::ToolButton(Gtk::Stock::CUT));
	this->append(*new Gtk::ToolButton(Gtk::Stock::PASTE));

	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND));
	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND_AND_REPLACE));

	this->append(*new Gtk::ToolButton(Gtk::Stock::PROPERTIES));
	this->show_all();
}
