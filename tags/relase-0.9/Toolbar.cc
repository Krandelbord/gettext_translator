#include "Toolbar.h"
#include "DictionariesMenu.h"
#include "config.h"

Toolbar::Toolbar() : m_spell_tb(Gtk::Stock::SPELL_CHECK) {

	this->set_tooltips(true);

	this->append(*new Gtk::ToolButton(Gtk::Stock::OPEN), m_signal_open_file);
	
	Gtk::ToolButton *ti = new Gtk::ToolButton(Gtk::Stock::SAVE);
	m_disable_list.push_back(ti);
	this->append(*ti, m_signal_save_file);

	this->append(*new Gtk::SeparatorToolItem());

	/*
	this->append(*new Gtk::ToolButton(Gtk::Stock::COPY));
	this->append(*new Gtk::ToolButton(Gtk::Stock::CUT));
	this->append(*new Gtk::ToolButton(Gtk::Stock::PASTE));
	this->append(*new Gtk::SeparatorToolItem());
	*/

	ti = new Gtk::ToolButton(Gtk::Stock::FIND);
	ti->signal_clicked().connect(m_signal_search);
	m_disable_list.push_back(ti);
	this->append(*ti);

	/*
	ti = new Gtk::ToolButton(Gtk::Stock::FIND_AND_REPLACE);
	ti->signal_clicked().connect(m_signal_search_and_replace);
	m_disable_list.push_back(ti);
	this->append(*ti);
	*/

	m_spell_tb.set_label(_("Spellcheker"));
	this->append(m_spell_tb);
	DictionariesMenu *dict_menu = new DictionariesMenu();
	dict_menu->signal_language_changed().connect(sigc::mem_fun(this, &Toolbar::onLanguageChanged));
	m_spell_tb.set_menu(*dict_menu);

	this->append(*new Gtk::SeparatorToolItem());

	Gtk::ToolButton *back_tb = new Gtk::ToolButton(Gtk::Stock::GO_BACK);
	m_disable_list.push_back(back_tb);
	back_tb->set_label(_("Back"));
	back_tb->set_tooltip(m_tooltips, _("Previous message"));
	back_tb->signal_clicked().connect(m_signal_previous_message);
	this->append(*back_tb);

	Gtk::ToolButton *forward_tb = new Gtk::ToolButton(Gtk::Stock::GO_FORWARD);
	m_disable_list.push_back(forward_tb);
	forward_tb->set_label(_("Next"));
	forward_tb->set_tooltip(m_tooltips, _("Next message"));
	forward_tb->signal_clicked().connect(m_signal_next_message); // propagate signal
	this->append(*forward_tb);

	Gtk::ToolButton *first_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_FIRST);
	m_disable_list.push_back(first_tb);
	first_tb->set_label(_("Previous"));
	first_tb->set_tooltip(m_tooltips, _("Jumps to previous fuzzy or untranslated message"));
	first_tb->signal_clicked().connect(m_signal_jump_previous_message);
	this->append(*first_tb);

	Gtk::ToolButton *last_tb = new Gtk::ToolButton(Gtk::Stock::GOTO_LAST);
	m_disable_list.push_back(last_tb);
	last_tb->set_label(_("Next"));
	last_tb->set_tooltip(m_tooltips, _("Jumps to next fuzzy or untranslated message"));
	last_tb->signal_clicked().connect(m_signal_jump_next_message);
	this->append(*last_tb);

	this->show_all();
}

void Toolbar::onLanguageChanged(const Glib::ustring &new_lang) {
	m_spell_tb.set_label(_("Spellcheker - ")+new_lang);
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

sigc::signal<void> &Toolbar::signal_search() {
	return m_signal_search;
}

sigc::signal<void> &Toolbar::signal_search_and_replace() {
	return m_signal_search_and_replace;
}

void Toolbar::disable_items() {
	for (ItemsList::iterator it = m_disable_list.begin(); it!=m_disable_list.end(); ++it) {
		(*it)->set_sensitive(false);
	}
}

void Toolbar::enable_items() {
	for (ItemsList::iterator it = m_disable_list.begin(); it!=m_disable_list.end(); ++it) {
		(*it)->set_sensitive(true);
	}
}
