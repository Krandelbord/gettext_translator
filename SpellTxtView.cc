#include "SpellTxtView.h"
#include "config.h"
#include "keys.h"

SpellTxtView::SpellTxtView() {
	m_gtk_spell = NULL;
}

void SpellTxtView::setLanguage(const Glib::ustring &lang) {
	debug("Setting spellcheker to %s\n", lang.c_str())
	if (m_gtk_spell != NULL) {
		GtkTextView *txt_view = this->gobj();
		gtkspell_detach(m_gtk_spell);
		m_gtk_spell = gtkspell_new_attach(GTK_TEXT_VIEW(txt_view), lang.c_str(), NULL);
	} else {
		GtkTextView *txt_view = this->gobj();
		m_gtk_spell = gtkspell_new_attach(GTK_TEXT_VIEW(txt_view), lang.c_str(), NULL);
	}
}

SpellTxtView::~SpellTxtView() {
	if (m_gtk_spell) gtkspell_detach(m_gtk_spell);
}

bool SpellTxtView::on_key_press_event(GdkEventKey* event) {
	if (KEY_COPY_MSGID) {
		// ctrl + space pressed
		m_signal_copy_msgid.emit();
	}
	if (KEY_TOGGLE_FUZZY) {
		m_signal_toggle_fuzzy.emit();
	}
	Gtk::TextView::on_key_press_event(event);
	return true;
}

sigc::signal<void> &SpellTxtView::signal_copy_msgid() {
	return m_signal_copy_msgid;
}

sigc::signal<void> &SpellTxtView::signal_toggle_fuzzy() {
	return m_signal_toggle_fuzzy;
}
