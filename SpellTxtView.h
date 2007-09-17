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
		sigc::signal<void> &signal_copy_msgid();
		sigc::signal<void> &signal_toggle_fuzzy();

		virtual ~SpellTxtView();

	private:
		bool on_key_press_event(GdkEventKey* event);;
		GtkSpell *m_gtk_spell;
		sigc::signal<void> m_signal_copy_msgid;
		sigc::signal<void> m_signal_toggle_fuzzy;
};
#endif /* SPELL_TXT_VIEW_H */
