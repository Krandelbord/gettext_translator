#ifndef TEXT_PANEL_H
#define TEXT_PANEL_H

#include <gtkmm.h>

class TextPanel : public Gtk::VBox {
	public:
		TextPanel(const Glib::ustring &title);
	private:
		Gtk::Label m_title_label;
		Gtk::TextView m_text_view;
};

#endif /* TEXT_PANEL_H */
