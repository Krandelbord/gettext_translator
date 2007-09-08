#ifndef PO_READER_H
#define PO_READER_H

#include <glibmm.h>
#include <gettext-po.h>

class PoReader {
	public:
		PoReader(const Glib::ustring &file_path);
		Glib::ustring getHeader(const Glib::ustring &header_name);
		Glib::ustring getEncoding();

		Glib::ustring getMsgid();
		bool nextMessage();
		bool previousMessage();

		~PoReader();
	private:
		po_file_t             m_pofile;
		Glib::ustring         m_file_encoding;
		po_message_iterator_t m_miter;
		po_message_t          m_current_msg;
		size_t				  m_msg_number;
};
#endif /* PO_READER_H */
