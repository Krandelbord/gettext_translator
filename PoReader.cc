#include "PoReader.h"
#include "config.h"

PoReader::PoReader(const Glib::ustring &file_path) {
	Glib::RefPtr<Glib::IOChannel> file = Glib::IOChannel::create_from_file(file_path, "r");
	Glib::ustring line;

	file->read_line(line);
	debug("Linia pierwsza = %s\n", line.c_str());
}
