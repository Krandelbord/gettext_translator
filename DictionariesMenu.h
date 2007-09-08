#ifndef DICTIONARIES_MENU_H
#define DICTIONARIES_MENU_H

#include <gtkmm.h>

class DictionariesMenu : public Gtk::Menu {
	public:
		DictionariesMenu();
		sigc::signal<void, Glib::ustring> &signal_language_changed();

	private:
		sigc::signal<void, Glib::ustring> m_signal_language_changed;
		void onMenuItemSelected(const Glib::ustring &new_lang);
};
#endif /* DICTIONARIES_MENU_H */
