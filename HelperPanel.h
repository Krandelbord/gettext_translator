#ifndef HELPER_PANEL_H
#define HELPER_PANEL_H

#include <gtkmm.h>

class HelperPanel : public Gtk::VBox {
	public:
		HelperPanel();
	private:
		Gtk::HBox m_main_box;
		Gtk::VSeparator m_vsep;
};

#endif /* HELPER_PANEL_H */
