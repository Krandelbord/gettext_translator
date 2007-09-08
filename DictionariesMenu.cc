#include "DictionariesMenu.h"
#include "Utils.h"

DictionariesMenu::DictionariesMenu() {
	std::vector<Glib::ustring> dict_list = getDictionaryList();
	for (std::vector<Glib::ustring>::iterator it = dict_list.begin(); it != dict_list.end(); ++it) {
		this->items().push_back( Gtk::Menu_Helpers::MenuElem(*it));
	}
}
