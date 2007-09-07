#include "PoReader.h"
#include "config.h"

PoReader::PoReader(const Glib::ustring &file_path) {
	po_xerror_handler_t error_handler;
	m_pofile = po_file_read(file_path.c_str(), error_handler);

	m_file_encoding = this->getEncoding();
}

Glib::ustring PoReader::getEncoding() {
	Glib::ustring content_type = this->getHeader("Content-Type");
	
	Glib::ustring::size_type charset_pos;
	charset_pos = content_type.find("=")+1;

	return content_type.substr(charset_pos);
}

Glib::ustring PoReader::getHeader(const Glib::ustring &header_name) {
	Glib::ustring retval;

	const char *header = po_file_domain_header(m_pofile, NULL);
	char *header_cstr = po_header_field(header, header_name.c_str());

	if (m_file_encoding.empty()) {
		retval=Glib::convert_with_fallback(header_cstr, "UTF-8", "iso-8859-1");
	} else retval=Glib::convert_with_fallback(header_cstr, "UTF-8", m_file_encoding);

	delete header_cstr;

	return retval;
}

PoReader::~PoReader() {
	po_file_free(m_pofile);
}
