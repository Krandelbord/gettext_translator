#include "TranslatedTextPanel.h"
#include "config.h"

TranslatedTextPanel::TranslatedTextPanel() {
	m_title_label.set_text("Transalted text (msgstr): ");
	m_title_label.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->pack_start(*new Gtk::HSeparator(), false, false);

	this->pack_start(m_title_box, false, false);

	m_title_box.pack_start(m_title_label, false, false);
	
	this->show_all_children();

	this->add(m_tr_tv);
}
