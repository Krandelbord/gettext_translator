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

guint PoReader::getPluralFormsNumber() {
	Glib::ustring plural_forms = this->getHeader("Plural-Forms");
	if (plural_forms.length()<=0) return 0;

	Glib::ustring::size_type pos = plural_forms.find("nplurals")+8; // 8 is length of "nplurals" string
	if (pos==Glib::ustring::npos) return 0; // Number of plural forms not defined. TODO: is this header malfolmed?

	pos = plural_forms.find("=", pos)+1;
	Glib::ustring::size_type end_pos = plural_forms.find(";", pos);
	Glib::ustring num = plural_forms.substr(pos, end_pos-pos);
	return atoi(num.c_str());
}

bool PoReader::jumpTo(size_t search_msg_number) {
	if (search_msg_number<=0) return false;
	//TODO: add checking if someone is trying to jump after end of the file
	//
	po_message_iterator_free(m_miter);
	m_miter = po_message_iterator(m_pofile, NULL);
	po_message_t msg;

	size_t cur_number = 0;
	do {
		msg = po_next_message(m_miter);
		cur_number++;
	} while (cur_number <= search_msg_number );
	
	if (msg) {
		m_msg_number = search_msg_number;
		m_current_msg = msg;
		return true;
	} else return false; /* TODO: if this return happens we we have iterarator 
						  * pointing to msgid = null.
						  *	But I guess it never happens.
						  */
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

	return this->jumpTo(m_msg_number-1);
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

void PoReader::setMsgstr(const Glib::ustring &msgstr) {
	po_message_set_msgstr(m_current_msg, Glib::convert_with_fallback(msgstr, m_file_encoding, "UTF-8").c_str());
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

void PoReader::setComments(const Glib::ustring &comments) {
	po_message_set_comments(m_current_msg, Glib::convert_with_fallback(comments, m_file_encoding, "UTF-8").c_str());
}

bool PoReader::isFuzzy() {
	return po_message_is_fuzzy(m_current_msg);
}

bool PoReader::isTranslated() {
	const char *msg_str = po_message_msgstr(m_current_msg);
	if (msg_str[0]=='\0') {
		return false;
	} else return true;
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

MsgContainer PoReader::getFilesUsage() {
	MsgContainer ret;

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

MsgContainer PoReader::getMsgstrPlural() {
	MsgContainer out;
	size_t index = 0;
	const char *msgstr_plural = NULL;
	do {
		msgstr_plural = po_message_msgstr_plural(m_current_msg, index);
		if (msgstr_plural) {
			Glib::ustring msg( Glib::convert_with_fallback(msgstr_plural, "UTF-8", m_file_encoding) );
			replaceAll(msg, "\n", "\\n\n");
			out.push_back(msg);
		}
		++index;
	} while(msgstr_plural)	;

	return out;
}

void PoReader::setMsgstrPlural(MsgContainer msgs) {
	guint num = 0;

	for (MsgContainer::iterator it = msgs.begin(); it!=msgs.end(); ++it, ++num) {
		Glib::ustring msg =	Glib::convert_with_fallback(*it, m_file_encoding, "UTF-8" );
		replaceAll(msg, "\\n\n", "\n");
		po_message_set_msgstr_plural(m_current_msg, num, msg.c_str());
	}
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
