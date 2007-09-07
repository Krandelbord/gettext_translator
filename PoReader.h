#ifndef PO_READER_H
#define PO_READER_H

#include <glibmm.h>

class PoReader {
	public:
		PoReader(const Glib::ustring &file_path);
		Glib::ustring getHeader(const Glib::ustring &header_name);
		Glib::ustring getEncoding();

	private:
		Glib::ustring m_file_path;
};
#endif /* PO_READER_H */
