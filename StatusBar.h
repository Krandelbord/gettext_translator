#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <gtkmm.h>

class StatusBar : public Gtk::Statusbar {
	public:
		StatusBar();
		void setCurrent(size_t n);
		void setFuzzy(size_t n);
		void setUntranslated(size_t n);

	private:
		Gtk::Statusbar m_current_sb;
		Gtk::Statusbar m_fuzzy_sb;
		Gtk::Statusbar m_untr_sb;

};
#endif /* STATUS_BAR_H */
