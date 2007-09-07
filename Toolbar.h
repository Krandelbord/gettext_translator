#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <gtkmm.h>
#include "PoReader.h"

class Toolbar : public Gtk::Toolbar {
	public:
		Toolbar(PoReader *po_reader);
		void setPoReader(PoReader *po_reader);
		sigc::signal<void> &signal_message_changed();

	private:
		PoReader *m_po_reader;
		void onNextClicked();
		sigc::signal<void>  m_signal_message_changed;
};

#endif /* TOOLBAR_H */
