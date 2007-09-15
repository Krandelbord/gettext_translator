#ifndef TRANSLATED_TEXT_PANEL_H
#define TRANSLATED_TEXT_PANEL_H

#include "TranslateTxtView.h"
#include "IndicatorWidget.h"

class TranslatedTextPanel : public Gtk::VBox {
	public:
		TranslatedTextPanel();
		void setText(const Glib::ustring &new_txt, bool is_fuzzy);
		void setText(std::vector<Glib::ustring> msgs, int plural_forms);
		void setSpellCheck(const Glib::ustring &spl_lang);
		Glib::ustring getText();

	private:
		Gtk::HBox m_title_box;
		Gtk::Label m_title_label;
		TranslateTxtView m_tr_tv;
		Gtk::HBox m_indicators_box;
		Gtk::Notebook m_notebook;
		std::list<TranslateTxtView*> m_tr_list;
		IndicatorWidget m_fuzzy_ind, m_untr_ind, m_err_ind;
};
#endif /* TRANSLATED_TEXT_PANEL_H */
