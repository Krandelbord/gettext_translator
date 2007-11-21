#include "ErrorHandlers.h"
#include <glibmm.h>
#include "config.h"
#include <sstream>

extern bool GLOBAL_ERROR_OCCURED;
extern Glib::ustring global_error_msg;

void xerror_handler (int severity,
		  po_message_t message,
		  const char *filename, size_t lineno, size_t column,
		  int multiline_p, const char *message_text) {

	GLOBAL_ERROR_OCCURED = true;
	std::ostringstream ss;

	ss << _("Problem in line") << " " << lineno;
	ss << " " << _("column") << " " << column << ": " << "\n\n";
	std::string charset;
	Glib::get_charset(charset);
	ss << Glib::convert(message_text, "UTF-8", charset);
	global_error_msg = ss.str();

	debug("\033[1;31mXerror %d handler \033[1;0m \n", severity);
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

	GLOBAL_ERROR_OCCURED = true;

	std::string charset;
	Glib::get_charset(charset);

	std::ostringstream ss;
	ss << _("Error in two messages\n");
	ss << _("First in line") << " " << lineno1 << " " << _("column") << " " << column1 << "\n";
	ss << Glib::convert(message_text1, "UTF-8", charset) << "\n\n";
	ss << _("Second in line") << " " << lineno2 << " " << _("column") << " " << column2 << "\n";
	ss << Glib::convert(message_text2, "UTF-8", charset) << "\n\n";

	global_error_msg = ss.str();

	debug("\033[1;31mXerror2 handler \033[1;0m\n");
	debug("Error int two messages:\n\tFirst in line %d column %d"
			"\n\tSecond in line %d column %d\n", 
			lineno1, column1, lineno2, column2);
	debug("Problem with first message %s\n", Glib::locale_to_utf8(message_text1).c_str());
	debug("Problem with second message %s\n", Glib::locale_to_utf8(message_text2).c_str());
}

