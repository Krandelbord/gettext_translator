#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar(Gtk::Window &main_win);

	private:
		Gtk::Menu *createFileMenu();
		void onQuitMenuitem();
		void onOpenMenuitem();
		Gtk::Window *m_main_win;
};

#endif /* MENU_BAR_H */

