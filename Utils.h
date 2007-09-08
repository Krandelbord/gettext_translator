#ifndef UTILS_H
#define UTILS_H

#include <glibmm.h>

std::vector<Glib::ustring> getDictionaryList();
void replaceAll(Glib::ustring &string, const Glib::ustring &search, const Glib::ustring &sub);
#endif /* UTILS_H */
