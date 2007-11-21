#include "ErrorHandlers.h"
#include <glibmm.h>
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

