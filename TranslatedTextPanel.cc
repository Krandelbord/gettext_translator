#include "TranslatedTextPanel.h"
#include "config.h"
#include "IndicatorWidget.h"

TranslatedTextPanel::TranslatedTextPanel() :
	m_fuzzy_ind("Fuzzy"), m_untr_ind("Untranslated"), m_err_ind("Error") {
	m_title_label.set_text("Transalted text (msgstr): ");
	m_title_label.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->pack_start(*new Gtk::HSeparator(), false, false);

	this->pack_start(m_title_box, false, false);

	m_title_box.pack_start(m_title_label, false, false);

	m_title_box.pack_end(m_indicators_box, false, false);

	m_indicators_box.pack_start(m_fuzzy_ind, false, false, 10);
	m_indicators_box.pack_start(m_untr_ind, false, false, 10);
	m_indicators_box.pack_start(m_err_ind, false, false, 10);
	
	this->show_all_children();

	this->add(m_tr_tv);
}
