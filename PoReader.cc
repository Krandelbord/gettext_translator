#include "PoReader.h"
#include "config.h"
#include <gettext-po.h>
PoReader::PoReader(const Glib::ustring &file_path) {
	po_xerror_handler_t error_handler;
	po_file_t pofile = po_file_read(file_path.c_str(), error_handler);
	const char *header = po_file_domain_header(pofile, NULL);
	debug("Hedaer = %s\n", header);
	debug("Last-Translator to %s\n", po_header_field(header, "Last-Translator"));
}

Glib::ustring PoReader::getEncoding() {
	return "";
}

Glib::ustring PoReader::getHeader(const Glib::ustring &header_name) {
	return "";
}
