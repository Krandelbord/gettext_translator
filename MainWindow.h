#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "TranslateTxtView.h"

class MainWindow : public Gtk::Window {
	public:
		MainWindow(guint width, guint hieght);

	private:
		Gtk::VBox m_box;
		Gtk::ComboBoxText m_combo;
		TranslateTxtView  m_tr_view;

		void onLanguageChanged();
};

#endif /* MAIN_WINDOW_H */
