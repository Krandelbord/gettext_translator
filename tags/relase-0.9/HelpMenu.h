#ifndef HELP_MENU_H
#define HELP_MENU_H

#include <gtkmm.h>

class HelpMenu : public Gtk::MenuBar {
	public:
		HelpMenu(Gtk::Window *main_win);
	private:
		void onAbout(Gtk::Window *main_win);

};

#endif /* HELP_MENU_H */
