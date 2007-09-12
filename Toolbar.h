#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <gtkmm.h>
#include "PoReader.h"

class Toolbar : public Gtk::Toolbar {
	public:
		Toolbar(PoReader *po_reader);
		void setPoReader(PoReader *po_reader);
		sigc::signal<void> &signal_message_changed();
		sigc::signal<void, Glib::ustring> &signal_language_changed();

	private:
		PoReader *m_po_reader;
		Gtk::Tooltips m_tooltips;

		void onNextClicked();
		void onPreviousClicked();
		void onLanguageChanged(const Glib::ustring &new_lang);

		sigc::signal<void>  m_signal_message_changed;
		sigc::signal<void, Glib::ustring> m_signal_language_changed;
};

#endif /* TOOLBAR_H */
