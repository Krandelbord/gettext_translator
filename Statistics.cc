#include "Statistics.h"
#include "ErrorHandlers.h"
#include "config.h"

Statistics::Statistics(const Glib::ustring &filename) {
	m_fuzzy_count = 0;
	m_untranslated_count = 0;
	m_msg_count = 0;

	struct po_xerror_handler error_handler;
	error_handler.xerror = xerror_handler;
	error_handler.xerror2 = xerror2_handler;

	po_file_t pofile = po_file_read(filename.c_str(), &error_handler);

	po_message_iterator_t iter = po_message_iterator(pofile, NULL);
	po_next_message(iter); //we skip header which is msgid

	po_message_t po_msg = NULL;
	do {
		po_msg = po_next_message(iter);
		if (po_msg) {
			if (po_message_is_fuzzy(po_msg)) m_fuzzy_count++;;
			if (!strlen(po_message_msgstr(po_msg))) m_untranslated_count++;
			if (!po_message_is_obsolete(po_msg)) ++m_msg_count;
		}
	} while (po_msg!=NULL);

	debug("Message count = %d; Untraslated = %d; Fuzzy = %d\n", m_msg_count, m_untranslated_count, m_fuzzy_count);

	po_message_iterator_free(iter);
	po_file_free(pofile);
}

