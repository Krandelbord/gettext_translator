#include "TranslatedTextPanel.h"
#include "config.h"
#include "IndicatorWidget.h"
#include <sstream>

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

	m_notebook.set_show_tabs(false);
	m_notebook.set_show_border(false);
	this->add(m_notebook);

	m_tr_tv.signal_copy_msgid().connect(m_signal_copy_msgid);
	m_notebook.append_page(m_tr_tv, "plural 1");
	m_tr_tv.set_wrap_mode(Gtk::WRAP_WORD);
	m_tr_list.push_back(&m_tr_tv);
}

void TranslatedTextPanel::setSpellCheck(const Glib::ustring &spl_lang) {
	m_tr_tv.setLanguage(spl_lang);
}

void TranslatedTextPanel::setText(const Glib::ustring &new_txt, bool is_fuzzy) {
	m_notebook.set_show_tabs(false);
	m_notebook.set_current_page(0);
	is_fuzzy ? m_fuzzy_ind.turnOn() : m_fuzzy_ind.turnOff();

	if (new_txt.length()==0) {
		m_untr_ind.turnOn();
	} else m_untr_ind.turnOff();

	Glib::RefPtr<Gtk::TextBuffer> buf = m_tr_tv.get_buffer();
	buf->set_text(new_txt);

	for (int i=1; i < m_notebook.get_n_pages(); ++i) {
		Gtk::Widget *wdg = m_notebook.get_nth_page(i);
		wdg->hide();
	}
}

void TranslatedTextPanel::setText(std::vector<Glib::ustring> msgs, int plural_forms, bool is_fuzzy) {
	is_fuzzy ? m_fuzzy_ind.turnOn() : m_fuzzy_ind.turnOff();
	m_notebook.set_current_page(0);
	
	if (m_notebook.get_n_pages() < plural_forms) {
		for (int i=m_notebook.get_n_pages(); i < plural_forms; ++i) {
			SpellTxtView *tr_tv = Gtk::manage(new SpellTxtView());
			tr_tv->signal_copy_msgid().connect(m_signal_copy_msgid);
			std::ostringstream ostr;
			ostr << "plural " << i+1;
			m_notebook.append_page(*tr_tv, ostr.str());
			m_tr_list.push_back(tr_tv);
		}
	} // hmm.. maybe we should sometimes delete pages if we don't need them

	guint num = 0;
	m_notebook.set_show_tabs(true);
	std::vector<Glib::ustring>::iterator it = msgs.begin();
	std::list<SpellTxtView*>::iterator tr_it = m_tr_list.begin();

	do {
		SpellTxtView *tr_tv = *tr_it;
		Glib::RefPtr<Gtk::TextBuffer> buf = tr_tv->get_buffer();
		if (it!=msgs.end()) {
			buf->set_text(*it);
			if ((*it).length()==0) m_untr_ind.turnOn();
		} else {
			m_untr_ind.turnOn();
			buf->set_text("");
		}

		++num;
		if (it!=msgs.end()) ++it;
		++tr_it;
	} while (tr_it!=m_tr_list.end());
	this->show_all();
}

Glib::ustring TranslatedTextPanel::getText() {
	Glib::RefPtr<Gtk::TextBuffer> buf = m_tr_tv.get_buffer();
	return buf->get_text();
}

std::vector<Glib::ustring> TranslatedTextPanel::getPluralTexts() {
	std::vector<Glib::ustring> txts;
	for (TrTViewList::iterator tr_it = m_tr_list.begin(); tr_it!=m_tr_list.end(); ++tr_it) {
		SpellTxtView *tr_tv = *tr_it;
		Glib::RefPtr<Gtk::TextBuffer> buf = tr_tv->get_buffer();
		txts.push_back(buf->get_text());
	}
	return txts;
}

sigc::signal<void> &TranslatedTextPanel::signal_copy_msgid() {
	return m_signal_copy_msgid;
}

bool TranslatedTextPanel::getFuzzy() {
	return m_fuzzy_ind.getStatus();
}
