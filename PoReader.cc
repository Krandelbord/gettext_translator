#include "PoReader.h"
#include "config.h"

PoReader::PoReader(const Glib::ustring &file_path) {

	m_file_path = file_path;
	Glib::RefPtr<Glib::IOChannel> file = Glib::IOChannel::create_from_file(file_path, "r");
	file->set_encoding(this->getEncoding());
	Glib::ustring line;

	file->read_line(line);
	Glib::ustring after, msgid, msgstr, comment;
	std::list<Glib::ustring> before;
	for (int i=0; i<3; ++i) {
		debug("Numer %d\n", i);

		do {
			file->read_line(line);
			if (line.find("#")==0) before.push_back(line);
		} while (line.find("msgid")!=0);

		if (line.length()>7) msgid+=line.substr(7, line.length()-7-2);
		for (std::list<Glib::ustring>::iterator it = before.begin(); it!=before.end(); ++it) {
			debug("Before msgid = %s\n", (*it).c_str());
		}

		bool first_msgid_line = true;
		do {
			file->read_line(line);
			if (line.find("\"")==0) {
				if (!first_msgid_line) {
					msgid+="\n";
				} else first_msgid_line = false;

				msgid+=line.substr(1, line.length()-3);
			}
			debug("after = %s\n", line.c_str());
		} while (line.find("msgstr")!=0);
		debug("Msgid = %s\n", msgid.c_str());

		before.clear();
		msgid.clear();
	}
}

Glib::ustring PoReader::getEncoding() {
	Glib::ustring content_type = getHeader("Content-Type");	
	int charset_pos = content_type.find("charset");
	int equals_pos  = content_type.find("=", charset_pos)+1;
	return content_type.substr(equals_pos);
}

Glib::ustring PoReader::getHeader(const Glib::ustring &header_name) {
	Glib::ustring header_value;

	Glib::RefPtr<Glib::IOChannel> file = Glib::IOChannel::create_from_file(m_file_path, "r");
	file->set_encoding("");
	Glib::ustring line;

	do {
		file->read_line(line);
	} while(line!="msgid \"\"\n");

	bool header_found = false;
	do {
		file->read_line(line);
		if (line.find(header_name, 1)==1) {
			int semi_pos = line.find(": ")+2;
			header_found = true;
			header_value = line.substr(semi_pos, line.length()-semi_pos-4);
		}
	} while(line.find("msgid")!=0);

	return header_value;
}
