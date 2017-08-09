#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "MenuBar.h"
#include "Toolbar.h"
#include "TextPanel.h"
#include "HelperPanel.h"
#include "PoReader.h"
#include "TranslatedTextPanel.h"
#include "StatusBar.h"

class MainWindow : public Gtk::Window {
	public:
		MainWindow(guint width, guint hieght);
		void onFileOpened(const Glib::ustring &file_path);

	private:
		void onPanedChaged(Gtk::Requisition *r);
		void onSizeChanged(Gtk::Requisition *r);
		bool on_delete_event(GdkEventAny *event);

		Gtk::HPaned m_hpan;
		Gtk::VPaned m_vpan;
		Gtk::VBox m_box;

		Toolbar m_toolbar;
		MenuBar m_menu_bar;
		TextPanel m_text_panel;
		HelperPanel m_helper_panel;
		TranslatedTextPanel m_tr_panel;
		StatusBar m_status_bar;
		PoReader *m_po_reader;

		/* Search options : */
		Glib::ustring m_last_search;
		Glib::ustring m_last_replace;
		bool m_search_ignore_case;
		bool m_search_msgstr;
		bool m_search_msgid;
		size_t m_msg_count;

		void fromGui2Po();
		void fromPo2Gui();
		void onLanguageChanged();
		void onNextMessage();
		void onPreviousMessage();
		void onJumpNextMessage();
		void onJumpPreviousMessage();
		void onJumpTo();
		void onOpenFile();
		void onSaveFile();
		void onHeaderEdit();
		void onCopyMsgid();
		void onSwitchFuzzy();
		bool searchExec();
		void onSearch();
		void onReplace();
		bool doReplace(const Glib::ustring &str1, const Glib::ustring &str2);
};

#endif /* MAIN_WINDOW_H */
