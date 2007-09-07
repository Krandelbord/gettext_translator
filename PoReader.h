#ifndef PO_READER_H
#define PO_READER_H

#include <glibmm.h>
#include <gettext-po.h>

class PoReader {
	public:
		PoReader(const Glib::ustring &file_path);
		Glib::ustring getHeader(const Glib::ustring &header_name);
		Glib::ustring getEncoding();

		~PoReader();
	private:
		po_file_t     m_pofile;
		Glib::ustring m_file_encoding;
};
#endif /* PO_READER_H */
