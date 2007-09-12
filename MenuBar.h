#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>
#include "PoReader.h"

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar(Gtk::Window &main_win, PoReader *po_reader);
		void setPoReader(PoReader *po_reader);
		sigc::signal<void> &signal_message_changed();

	private:
		PoReader *m_po_reader;
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		void onOpenMenuitem();
		void onJumpTo();
		Gtk::Window *m_main_win;
		sigc::signal<void>  m_signal_message_changed;
};

#endif /* MENU_BAR_H */

