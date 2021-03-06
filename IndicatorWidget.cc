#include "IndicatorWidget.h"

IndicatorWidget::IndicatorWidget(const Glib::ustring &name, Gdk::Color off_color, Gdk::Color on_color) {
	m_status=false;
	m_off_color = off_color;
	m_on_color = on_color;

	m_Frame.set_shadow_type(Gtk::SHADOW_IN);
	m_Label.set_text(name);
	m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, off_color);

	m_Frame.add(m_DrawingArea);
	this->pack_start(m_Frame, false, false, 2);
	this->pack_end(m_Label, false, false);
	
	m_Label.show_all();
	Glib::RefPtr<Pango::Layout> pango = m_Label.get_layout();
	int wi, hi;
	pango->get_pixel_size(wi, hi);
	m_DrawingArea.set_size_request(hi-5, hi-5);

	this->show_all();
}

void IndicatorWidget::turnOn() {
	m_status = true;
	m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_on_color);
}

void IndicatorWidget::turnOff() {
	m_status = false;
	m_DrawingArea.modify_bg(Gtk::STATE_NORMAL, m_off_color);
}

bool IndicatorWidget::getStatus() {
	return m_status;
}
