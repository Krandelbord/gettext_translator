#include "Toolbar.h"

Toolbar::Toolbar(PoReader *po_reader) {
	m_po_reader = po_reader;
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
	//first_tb->set_state(Gtk::STATE_INSENSITIVE);
	first_tb->set_label("Previous");
	first_tb->set_tooltip(*tooltips, "Jumps to previous fuzzy or untranslated message");
	first_tb->signal_clicked().connect(sigc::mem_fun(this, &Toolbar::onPreviousClicked));
	this->append(*first_tb);

	Gtk::ToolButton *last_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_LAST);
	last_tb->set_label("Next");
	last_tb->set_tooltip(*tooltips, "Jumps to next fuzzy or untranslated message");
	last_tb->signal_clicked().connect(sigc::mem_fun(this, &Toolbar::onNextClicked));
	this->append(*last_tb);

	this->show_all();
}

void Toolbar::onPreviousClicked() {
	if (m_po_reader->previousMessage()) m_signal_message_changed.emit();
}

void Toolbar::onNextClicked() {
	if (m_po_reader->nextMessage()) m_signal_message_changed.emit();
}

sigc::signal<void> &Toolbar::signal_message_changed() {
	return m_signal_message_changed;
}

void Toolbar::setPoReader(PoReader *po_reader) {
	m_po_reader = po_reader;
}
