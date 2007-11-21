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
		Glib::ustring::size_type search_start = found_pos+sub.length();
		string.replace(found_pos, search.length(), sub);
		found_pos = string.find(search, search_start);
	}
}

Glib::ustring replaceAllReturn(const Glib::ustring &string, const Glib::ustring &search, const Glib::ustring &sub) {
	Glib::ustring retval(string);
	replaceAll(retval, search, sub);
	return retval;
}

bool compare(const Glib::ustring &str1, const Glib::ustring &str2) {
	if (str1.find(str2)!=Glib::ustring::npos) return true;
	return false;
}

bool IcaseCompare(const Glib::ustring &str1, const Glib::ustring &str2) {
	Glib::ustring u_str1 = str1.lowercase();
	Glib::ustring u_str2 = str2.lowercase();

	if (u_str1.find(u_str2)!=Glib::ustring::npos) return true;
	return false;
}

