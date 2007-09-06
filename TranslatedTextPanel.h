#ifndef TRANSLATED_TEXT_PANEL_H
#define TRANSLATED_TEXT_PANEL_H

#include "TranslateTxtView.h"

class TranslatedTextPanel : public Gtk::VBox {
	public:
		TranslatedTextPanel();
	private:
		Gtk::HBox m_title_box;
		Gtk::Label m_title_label;
		TranslateTxtView m_tr_tv;
};
#endif /* TRANSLATED_TEXT_PANEL_H */
