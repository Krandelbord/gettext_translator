#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar();
		sigc::signal<void> &signal_jump_to();
		sigc::signal<void> &signal_open_file();
		sigc::signal<void> &signal_header_edit();
		sigc::signal<void> &signal_switch_fuzzy();
		sigc::signal<void> &signal_next_msg();
		sigc::signal<void> &signal_prev_msg();
		sigc::signal<void> &signal_jump_next_msg();
		sigc::signal<void> &signal_jump_prev_msg();

	private:
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		sigc::signal<void>  m_signal_jump_to;
		sigc::signal<void>  m_signal_open_file;
		sigc::signal<void>  m_signal_header_edit;
		sigc::signal<void>  m_signal_switch_fuzzy;
		sigc::signal<void>  m_signal_next_msg;
		sigc::signal<void>  m_signal_prev_msg;
		sigc::signal<void>  m_signal_jump_next_msg;
		sigc::signal<void>  m_signal_jump_prev_msg;
};

#endif /* MENU_BAR_H */

