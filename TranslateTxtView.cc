#include "TranslateTxtView.h"
#include "config.h"

TranslateTxtView::TranslateTxtView() {
	m_gtk_spell = NULL;
}

void TranslateTxtView::setLanguage(const Glib::ustring &lang) {
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

TranslateTxtView::~TranslateTxtView() {
	if (m_gtk_spell) gtkspell_detach(m_gtk_spell);
}
