#ifndef ERROR_HANDLERS_H
#define ERROR_HANDLERS_H

#include <gettext-po.h>

void xerror_handler (int severity,
		  po_message_t message,
		  const char *filename, size_t lineno, size_t column,
		  int multiline_p, const char *message_text);

void xerror2_handler(int severity,
		   po_message_t message1,
		   const char *filename1, size_t lineno1, size_t column1,
		   int multiline_p1, const char *message_text1,
		   po_message_t message2,
		   const char *filename2, size_t lineno2, size_t column2,
		   int multiline_p2, const char *message_text2);

#endif /* ERROR_HANDLERS_H */
