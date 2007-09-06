#ifndef TRANSLATED_TEXT_PANEL_H
#define TRANSLATED_TEXT_PANEL_H

#include "TranslateTxtView.h"
#include "IndicatorWidget.h"

class TranslatedTextPanel : public Gtk::VBox {
	public:
		TranslatedTextPanel();
	private:
		Gtk::HBox m_title_box;
		Gtk::Label m_title_label;
		TranslateTxtView m_tr_tv;
		Gtk::HBox m_indicators_box;
		IndicatorWidget m_fuzzy_ind, m_untr_ind, m_err_ind;
};
#endif /* TRANSLATED_TEXT_PANEL_H */
