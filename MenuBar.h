#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>
#include "PoReader.h"

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar(Gtk::Window &main_win, PoReader *po_reader);
		void setPoReader(PoReader *po_reader);
		sigc::signal<void> &signal_jump_to();

	private:
		PoReader *m_po_reader;
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		void onOpenMenuitem();
		Gtk::Window *m_main_win;
		sigc::signal<void>  m_signal_jump_to;
};

#endif /* MENU_BAR_H */

