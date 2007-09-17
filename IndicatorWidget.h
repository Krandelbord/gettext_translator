#ifndef INDICATOR_WIDGET_H
#define INDICATOR_WIDGET_H

#include <gtkmm.h>

class IndicatorWidget : public Gtk::HBox {
	public:
		IndicatorWidget(const Glib::ustring &name, Gdk::Color off_color=Gdk::Color("brown"),Gdk::Color on_color=Gdk::Color("red"));
		void turnOn();
		void turnOff();
		bool getStatus();

	private:
		Gtk::DrawingArea m_DrawingArea;
		Gtk::Frame		 m_Frame;
		Gtk::Label		 m_Label;
		Gdk::Color		 m_off_color, m_on_color;
		bool 			 m_status;
};

#endif /* INDICATOR_WIDGET_H */
