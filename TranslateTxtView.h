#ifndef TRANSLATE_TXT_VIEW_H
#define TRANSLATE_TXT_VIEW_H

#include <gtkmm.h>
extern "C" {
	#include <gtk/gtk.h>
	#include <gtkspell/gtkspell.h>
}

class TranslateTxtView : public Gtk::TextView {
	public:
		TranslateTxtView();
		void setLanguage(const Glib::ustring &lang);

		virtual ~TranslateTxtView();

	private:
		GtkSpell *m_gtk_spell;
};
#endif /* TRANSLATE_TXT_VIEW_H */
