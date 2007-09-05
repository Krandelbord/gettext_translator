#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar();

	private:
		Gtk::Menu *createFileMenu();
		void onQuitMenuitem();
		void onOpenMenuitem();
};

#endif /* MENU_BAR_H */

