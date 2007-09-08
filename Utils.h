#ifndef UTILS_H
#define UTILS_H

#include <glibmm.h>

std::vector<Glib::ustring> getDictionaryList();
/*
 * replaces all occurences of @search in @string with @sub
 */
void replaceAll(Glib::ustring &string, const Glib::ustring &search, const Glib::ustring &sub);

/*
 * It does exactly the same but returns new string
 */
Glib::ustring replaceAllReturn(const Glib::ustring &string, const Glib::ustring &search, const Glib::ustring &sub);

#endif /* UTILS_H */
