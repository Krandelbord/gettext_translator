#include "Toolbar.h"
#include "DictionariesMenu.h"
#include "config.h"

Toolbar::Toolbar(PoReader *po_reader) : m_spell_tb(Gtk::Stock::SPELL_CHECK) {
	m_po_reader = po_reader;
	this->set_tooltips(true);

	this->append(*new Gtk::ToolButton(Gtk::Stock::OPEN), m_signal_open_file);
	this->append(*new Gtk::ToolButton(Gtk::Stock::SAVE), m_signal_save_file);
	this->append(*new Gtk::SeparatorToolItem());

	/*
	this->append(*new Gtk::ToolButton(Gtk::Stock::COPY));
	this->append(*new Gtk::ToolButton(Gtk::Stock::CUT));
	this->append(*new Gtk::ToolButton(Gtk::Stock::PASTE));
	this->append(*new Gtk::SeparatorToolItem());
	*/

	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND));
	this->append(*new Gtk::ToolButton(Gtk::Stock::FIND_AND_REPLACE));

	m_spell_tb.set_label("Spellcheker");
	this->append(m_spell_tb);
	DictionariesMenu *dict_menu = new DictionariesMenu();
	dict_menu->signal_language_changed().connect(sigc::mem_fun(this, &Toolbar::onLanguageChanged));
	m_spell_tb.set_menu(*dict_menu);

	this->append(*new Gtk::SeparatorToolItem());

	Gtk::ToolButton *back_tb = new Gtk::ToolButton(Gtk::Stock::GO_BACK);
	back_tb->set_label("Back");
	back_tb->set_tooltip(m_tooltips, "Previous message");
	back_tb->signal_clicked().connect(m_signal_previous_message);
	this->append(*back_tb);

	Gtk::ToolButton *forward_tb = new Gtk::ToolButton(Gtk::Stock::GO_FORWARD);
	forward_tb->set_label("Next");
	forward_tb->set_tooltip(m_tooltips, "Next message");
	forward_tb->signal_clicked().connect(m_signal_next_message); // propagate signal
	this->append(*forward_tb);

	Gtk::ToolButton *first_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_FIRST);
	//first_tb->set_state(Gtk::STATE_INSENSITIVE);
	first_tb->set_label("Previous");
	first_tb->set_tooltip(m_tooltips, "Jumps to previous fuzzy or untranslated message");
	first_tb->signal_clicked().connect(m_signal_jump_previous_message);
	this->append(*first_tb);

	Gtk::ToolButton *last_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_LAST);
	last_tb->set_label("Next");
	last_tb->set_tooltip(m_tooltips, "Jumps to next fuzzy or untranslated message");
	last_tb->signal_clicked().connect(m_signal_jump_next_message);
	this->append(*last_tb);

	this->show_all();
}

void Toolbar::onLanguageChanged(const Glib::ustring &new_lang) {
	m_spell_tb.set_label("Spellcheker - "+new_lang);
	m_signal_language_changed.emit(new_lang);
}

sigc::signal<void> &Toolbar::signal_message_changed() {
	return m_signal_message_changed;
}

sigc::signal<void> &Toolbar::signal_next_message() {
	return m_signal_next_message;
}

sigc::signal<void> &Toolbar::signal_jump_next_message() {
	return m_signal_jump_next_message;
}

sigc::signal<void> &Toolbar::signal_previous_message() {
	return m_signal_previous_message;
}

sigc::signal<void> &Toolbar::signal_jump_previous_message() {
	return m_signal_jump_previous_message;
}

sigc::signal<void, Glib::ustring> &Toolbar::signal_language_changed() {
	return m_signal_language_changed;
}

sigc::signal<void> &Toolbar::signal_open_file() {
	return m_signal_open_file;
}

sigc::signal<void> &Toolbar::signal_save_file() {
	return m_signal_save_file;
}

void Toolbar::setPoReader(PoReader *po_reader) {
	m_po_reader = po_reader;
}
