#include "Toolbar.h"

Toolbar::Toolbar() {
	this->set_tooltips(true);

	this->append(*new Gtk::ToolButton(Gtk::Stock::OPEN));
	this->append(*new Gtk::ToolButton(Gtk::Stock::SAVE));
	this->append(*new Gtk::SeparatorToolItem());

	this->append(*new Gtk::ToolButton(Gtk::Stock::COPY));
	this->append(*new Gtk::ToolButton(Gtk::Stock::CUT));
	this->append(*new Gtk::ToolButton(Gtk::Stock::PASTE));
	this->append(*new Gtk::SeparatorToolItem());

	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND));
	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND_AND_REPLACE));
	this->append(*new Gtk::SeparatorToolItem());

	this->append(*new Gtk::ToolButton(Gtk::Stock::GO_BACK));
	this->append(*new Gtk::ToolButton(Gtk::Stock::GO_FORWARD));

	Gtk::Tooltips *tooltips = new Gtk::Tooltips();

	Gtk::ToolButton *first_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_FIRST);
	first_tb->set_label("Previous");
	first_tb->set_tooltip(*tooltips, "Jumps to previous fuzzy or untranslated message");

	Gtk::ToolButton *last_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_LAST);
	last_tb->set_label("Next");
	last_tb->set_tooltip(*tooltips, "Jumps to next fuzzy or untranslated message");
	this->append(*first_tb);
	this->append(*last_tb);

	this->show_all();
}
