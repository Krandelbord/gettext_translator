#include "Utils.h"
#include <aspell.h>
#include <vector>

std::vector<Glib::ustring> getDictionaryList() {
	std::vector<Glib::ustring> list;

	
	
	struct AspellConfig *a_config = new_aspell_config();
	
	AspellDictInfoList *dlist = get_aspell_dict_info_list(a_config);
	AspellDictInfoEnumeration *dels = aspell_dict_info_list_elements(dlist);
	const AspellDictInfo *entry;
	while ( (entry = aspell_dict_info_enumeration_next(dels)) != 0) {
		list.push_back(entry->name);
	}

	return list;
}

void replaceAll(Glib::ustring &string, const Glib::ustring &search, const Glib::ustring &sub) {
	Glib::ustring::size_type found_pos = string.find(search);
	while (found_pos!=Glib::ustring::npos) {
		string.replace(found_pos, search.length(), sub);
		found_pos = string.find(search, found_pos+search.length());
	}
}
