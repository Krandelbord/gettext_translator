#ifndef INDICATOR_WIDGET_H
#define INDICATOR_WIDGET_H

#include <gtkmm.h>

class IndicatorWidget : public Gtk::HBox {
	public:
		IndicatorWidget(const Glib::ustring &name, Gdk::Color off_color, Gdk::Color on_color);
	private:
		Gtk::DrawingArea m_DrawingArea;
		Gtk::Frame		 m_Frame;
		Gtk::Label		 m_Label;

};

#endif /* INDICATOR_WIDGET_H */
