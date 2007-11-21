#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <gtkmm.h>

class StatusBar : public Gtk::Statusbar {
	public:
		StatusBar();
		void   setTotal(size_t n);
		void   setCurrent(size_t n);
		void   setFuzzy(size_t n);
		size_t getFuzzy();
		void setUntranslated(size_t n);
		size_t getUntranslated();

	private:
		Gtk::Statusbar m_total_sb;
		Gtk::Statusbar m_fuzzy_sb;
		Gtk::Statusbar m_untr_sb;
		size_t m_fuzzy, m_untr;

};
#endif /* STATUS_BAR_H */
