#ifndef STATISTICS_H
#define STATISTICS_H

#include <glibmm.h>

class Statistics {
	public:
		Statistics(const Glib::ustring &filename);
	private:
		size_t m_fuzzy_count, m_msg_count, m_untranslated_count;
};
#endif /* STATISTICS_H */
