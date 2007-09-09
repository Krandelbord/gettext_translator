#ifndef STATISTICS_H
#define STATISTICS_H

#include <glibmm.h>

class Statistics {
	public:
		Statistics(const Glib::ustring &filename);

		size_t getTotal() const;
		size_t getFuzzy() const;
		size_t getUntranslated() const;
	private:
		size_t m_fuzzy_count, m_msg_count, m_untranslated_count;
};
#endif /* STATISTICS_H */
