#include "DictionariesMenu.h"
#include "Utils.h"
#include "config.h"

DictionariesMenu::DictionariesMenu() {
	this->set_title("Change spellcheker dictionary");
	std::vector<Glib::ustring> dict_list = getDictionaryList();
	for (std::vector<Glib::ustring>::iterator it = dict_list.begin(); it != dict_list.end(); ++it) {
		this->items().push_back( 
				Gtk::Menu_Helpers::MenuElem(*it,
					sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &DictionariesMenu::onMenuItemSelected), *it) 
					)
				);
	}
}

void DictionariesMenu::onMenuItemSelected(const Glib::ustring &new_lang) {
	m_signal_language_changed.emit(new_lang);
}

sigc::signal<void, Glib::ustring> &DictionariesMenu::signal_language_changed() {
	return m_signal_language_changed;
}
