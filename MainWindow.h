#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "Toolbar.h"
#include "TextPanel.h"
#include "PoReader.h"
#include "TranslatedTextPanel.h"
#include "StatusBar.h"

class MainWindow : public Gtk::Window {
	public:
		MainWindow(guint width, guint hieght);
		void onFileOpened(const Glib::ustring &file_path);

	private:
		void onPanedChaged(Gtk::Requisition *r);
		void onSizeChanged(Gtk::Requisition *r);

		Gtk::HPaned m_hpan;
		Gtk::VPaned m_vpan;
		Gtk::VBox m_box;

		Toolbar m_toolbar;
		TextPanel m_text_panel;
		TranslatedTextPanel m_tr_panel;
		StatusBar m_status_bar;
		PoReader *m_po_reader;

		void onLanguageChanged();
		void onMessageChanged();
};

#endif /* MAIN_WINDOW_H */
