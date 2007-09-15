#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar();
		sigc::signal<void> &signal_jump_to();

	private:
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		void onOpenMenuitem();
		sigc::signal<void>  m_signal_jump_to;
};

#endif /* MENU_BAR_H */

