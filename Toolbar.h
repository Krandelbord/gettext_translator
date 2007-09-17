#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <gtkmm.h>


class Toolbar : public Gtk::Toolbar {
	public:
		Toolbar();
		sigc::signal<void> &signal_message_changed();
		sigc::signal<void> &signal_next_message();
		sigc::signal<void> &signal_jump_next_message();
		sigc::signal<void> &signal_previous_message();
		sigc::signal<void> &signal_jump_previous_message();
		sigc::signal<void, Glib::ustring> &signal_language_changed();
		sigc::signal<void> &signal_open_file();
		sigc::signal<void> &signal_save_file();

	private:
		Gtk::Tooltips m_tooltips;
		Gtk::MenuToolButton m_spell_tb;

		void onLanguageChanged(const Glib::ustring &new_lang);

		sigc::signal<void>  m_signal_message_changed;
		sigc::signal<void>  m_signal_next_message;
		sigc::signal<void>  m_signal_jump_next_message;
		sigc::signal<void>  m_signal_previous_message;
		sigc::signal<void>  m_signal_jump_previous_message;
		sigc::signal<void>  m_signal_open_file;
		sigc::signal<void>  m_signal_save_file;

		sigc::signal<void, Glib::ustring> m_signal_language_changed;
};

#endif /* TOOLBAR_H */
