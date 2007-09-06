#include "TextPanel.h"
#include "TranslateTxtView.h"

TextPanel::TextPanel(const Glib::ustring &title) : m_title_label(title) {
	this->pack_start(m_title_label, false, false);
	m_title_label.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->pack_end(m_text_view);
}
