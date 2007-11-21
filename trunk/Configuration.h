#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <glibmm.h>
#include <glib.h>
#include <string>

class Configuration {
	public:
		Configuration();
		void setValue(const Glib::ustring &category, const Glib::ustring &name, int value);
		int getValue(const Glib::ustring &category, const Glib::ustring &name) const;

		~Configuration();
	private:
		GKeyFile *m_key_file;
		char *m_file;
};

#endif /* CONFIGURATION_H */
