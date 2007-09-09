#include "Statistics.h"
#include "ErrorHandlers.h"
#include "config.h"

Statistics::Statistics(const Glib::ustring &filename) {
	struct po_xerror_handler error_handler;
	error_handler.xerror = xerror_handler;
	error_handler.xerror2 = xerror2_handler;

	po_file_t pofile = po_file_read(filename.c_str(), &error_handler);

	po_message_iterator_t iter = po_message_iterator(pofile, NULL);
	po_next_message(iter); //we skip header which is msgid

	size_t fuzzys = 0;
	size_t untranslated = 0;
	size_t msg_count = 0;

	po_message_t po_msg = NULL;
	do {
		po_msg = po_next_message(iter);
		if (po_msg && po_message_is_fuzzy(po_msg)) fuzzys++;;
		if (po_msg) debug("po-message = %s\n", po_message_msgid(po_msg));
	} while (po_msg!=NULL);

	debug("Mamy %d - wszystkie, %d nieprzet³umaczone %d fuzzy\n", msg_count, untranslated, fuzzys);
	po_message_iterator_free(iter);
	po_file_free(pofile);
}
