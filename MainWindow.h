#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "Toolbar.h"

class MainWindow : public Gtk::Window {
	public:
		MainWindow(guint width, guint hieght);

	private:
		void onPanedChaged(Gtk::Requisition *r);
		void onSizeChanged(Gtk::Requisition *r);

		Gtk::HPaned m_hpan;
		Gtk::VPaned m_vpan;
		Gtk::VBox m_box;

		Toolbar m_toolbar;

		void onLanguageChanged();
};

#endif /* MAIN_WINDOW_H */
