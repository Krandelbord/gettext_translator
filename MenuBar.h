#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar();
		sigc::signal<void> &signal_jump_to();
		sigc::signal<void> &signal_open_file();
		sigc::signal<void> &signal_header_edit();

	private:
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		sigc::signal<void>  m_signal_jump_to;
		sigc::signal<void>  m_signal_open_file;
		sigc::signal<void>  m_signal_header_edit;
};

#endif /* MENU_BAR_H */

