#include "PoReader.h"
#include "config.h"
void xerror_handler (int severity,
		  po_message_t message,
		  const char *filename, size_t lineno, size_t column,
		  int multiline_p, const char *message_text) {
	debug("\033[1;31mXerror handler \033[1;0m \n");
	debug("Problem in line %d column %d decsription: %s\n", 
			lineno, column,
			Glib::locale_to_utf8(message_text).c_str());
}

void xerror2_handler(int severity,
		   po_message_t message1,
		   const char *filename1, size_t lineno1, size_t column1,
		   int multiline_p1, const char *message_text1,
		   po_message_t message2,
		   const char *filename2, size_t lineno2, size_t column2,
		   int multiline_p2, const char *message_text2) {
	debug("\033[1;31mXerror2 handler \033[1;0m\n");
	debug("Error int two messages:\n\tFirst in line %d column %d"
			"\n\tSecond in line %d column %d\n", 
			lineno1, column1, lineno2, column2);
	debug("Problem with first message %s\n", Glib::locale_to_utf8(message_text1).c_str());
	debug("Problem with second message %s\n", Glib::locale_to_utf8(message_text2).c_str());
}


PoReader::PoReader(const Glib::ustring &file_path) {
	m_msg_number = 0;
	struct po_xerror_handler error_handler;
	error_handler.xerror = xerror_handler;
	error_handler.xerror2 = xerror2_handler;
	debug("Otwieranie pliku %s\n", file_path.c_str());
	m_pofile = po_file_read(file_path.c_str(), &error_handler);

	m_file_encoding = this->getEncoding();

	m_miter = po_message_iterator(m_pofile, NULL);
	po_next_message(m_miter);
	/*
	size_t fuzzys = 0;
	po_message_t po_msg = NULL;
	do {
		po_msg = po_next_message(m_miter);
		//++fuzzys;
		if (po_msg && po_message_is_fuzzy(po_msg)) fuzzys++;;
		if (po_msg) debug("po-message = %s\n", po_message_msgid(po_msg));
	} while (po_msg!=NULL);
	debug("Mamy %d fuzzy\n", fuzzys);
	*/
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

bool PoReader::nextMessage() {
	po_message_t msg = po_next_message(m_miter);
	if (msg) {
		m_msg_number++;
		m_current_msg = msg;
		return true;
	} else {
		debug("Nastepna wiadomosc - ERRRO \n");
		return false;
	}
}

bool PoReader::previousMessage() {
	if (m_msg_number<=1) return false;

	po_message_iterator_free(m_miter);
	m_miter = po_message_iterator(m_pofile, NULL);
	po_message_t msg;
	debug("We are looking for msg number %d\n", m_msg_number-1);
	size_t cur_number = 0;
	do {
		msg = po_next_message(m_miter);
		cur_number++;
	} while (cur_number < m_msg_number-1);

	if (msg) {
		m_msg_number-=1;
		m_current_msg = msg;
		return true;
	} else return false;
}

Glib::ustring PoReader::getMsgid() {
	Glib::ustring retval = Glib::convert_with_fallback(po_message_msgid(m_current_msg), "UTF-8", m_file_encoding);
	Glib::ustring::size_type newline_pos = retval.find('\n');
	
	while (newline_pos!=std::string::npos) {
		retval.insert(newline_pos, "\\n");
		newline_pos = retval.find(newline_pos+3, '\n');
	} 
	return retval;
}

void PoReader::saveToFile(const Glib::ustring &out_fname) {
	debug("Zapis do pliku %s\n", out_fname.c_str());
	struct po_xerror_handler error_handler;
	error_handler.xerror = xerror_handler;
	error_handler.xerror2 = xerror2_handler;

	po_file_t out_file = po_file_write(m_pofile, out_fname.c_str(), &error_handler);
	if (!out_file) debug("ERRROR przy zapisie\n"); 
}

PoReader::~PoReader() {
	po_message_iterator_free(m_miter);
	po_file_free(m_pofile);
}
