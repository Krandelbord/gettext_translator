#include "PoReader.h"
#include "Utils.h"
#include <sstream>
#include "ErrorHandlers.h"
#include "config.h"

PoReader::PoReader(const Glib::ustring &file_path) {
	m_msg_number = 0;
	struct po_xerror_handler error_handler;
	error_handler.xerror = xerror_handler;
	error_handler.xerror2 = xerror2_handler;
	debug("Otwieranie pliku %s\n", file_path.c_str());
	m_pofile = po_file_read(file_path.c_str(), &error_handler);

	m_file_encoding = this->getEncoding();

	m_miter = po_message_iterator(m_pofile, NULL);
	po_next_message(m_miter); //we skip header which is msgid

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
	} while (cur_number <= m_msg_number-1);

	if (msg) {
		m_msg_number-=1;
		m_current_msg = msg;
		return true;
	} else return false;
}

Glib::ustring PoReader::getMsgid() {
	debug("Message number %d\n", m_msg_number);
	Glib::ustring retval = Glib::convert_with_fallback(po_message_msgid(m_current_msg), "UTF-8", m_file_encoding);

	replaceAll(retval, "\n", "\\n\n");

	return retval;
}

Glib::ustring PoReader::getMsgstr() {
	Glib::ustring retval = Glib::convert_with_fallback(po_message_msgstr(m_current_msg), "UTF-8", m_file_encoding);
	replaceAll(retval, "\n", "\\n\n");
	return retval;
}

Glib::ustring PoReader::getMsgctx() {
	const char *ctx_cstr = po_message_msgctxt(m_current_msg);
	if (ctx_cstr) {
		return Glib::convert_with_fallback(ctx_cstr, "UTF-8", m_file_encoding);
	} else return Glib::ustring("");
}

Glib::ustring PoReader::getExtractedComments() {
	return Glib::convert_with_fallback(po_message_extracted_comments(m_current_msg), "UTF-8", m_file_encoding);
}

Glib::ustring PoReader::getComments() {
	return Glib::convert_with_fallback(po_message_comments(m_current_msg), "UTF-8", m_file_encoding);
}

bool PoReader::isFuzzy() {
	return po_message_is_fuzzy(m_current_msg);
}

bool PoReader::isCFormat() {
	return po_message_is_format(m_current_msg, "c-format");
}

bool PoReader::isObsolete() {
	return po_message_is_obsolete(m_current_msg);
}

size_t PoReader::getMessageNumber() {
	return m_msg_number;
}

std::vector<Glib::ustring> PoReader::getFilesUsage() {
	std::vector<Glib::ustring> ret;

	size_t index=0;
	po_filepos_t file_position;
	do {
		file_position = po_message_filepos(m_current_msg, index);
		if (file_position) {
			std::ostringstream out;
			out << po_filepos_file(file_position);
			out << ":" << po_filepos_start_line(file_position);
			ret.push_back(out.str());
		}
		++index;
	} while (file_position);

	return ret;
}

std::vector<Glib::ustring> PoReader::getMsgstrPlural() {
	std::vector<Glib::ustring> out;
	size_t index = 0;
	const char *msgstr_plural = NULL;
	do {
		msgstr_plural = po_message_msgstr_plural(m_current_msg, index);
		if (msgstr_plural) {
			Glib::ustring msg(msgstr_plural);
			replaceAll(msg, "\n", "\\n\n");
			out.push_back(msg);
		}
		++index;
	} while(msgstr_plural)	;

	return out;
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
