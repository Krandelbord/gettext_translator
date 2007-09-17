#ifndef SPELL_TXT_VIEW_H
#define SPELL_TXT_VIEW_H

#include <gtkmm.h>
extern "C" {
	#include <gtk/gtk.h>
	#include <gtkspell/gtkspell.h>
}

class SpellTxtView : public Gtk::TextView {
	public:
		SpellTxtView();
		void setLanguage(const Glib::ustring &lang);

		virtual ~SpellTxtView();

	private:
		GtkSpell *m_gtk_spell;
};
#endif /* SPELL_TXT_VIEW_H */
