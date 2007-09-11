#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class MenuBar : public Gtk::MenuBar {
	public:
		MenuBar(Gtk::Window &main_win);

	private:
		Gtk::Menu *createFileMenu();
		Gtk::Menu *createEditMenu();
		Gtk::Menu *createToolsMenu();

		void onQuitMenuitem();
		void onOpenMenuitem();
		void onJumpTo();
		Gtk::Window *m_main_win;
};

#endif /* MENU_BAR_H */

