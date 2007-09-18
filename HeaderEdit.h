#ifndef HEADER_EDIT_H
#define HEADER_EDIT_H

#include <gtkmm.h>
#include "PoReader.h"

class HeaderEdit : public Gtk::Window {
	public:
		HeaderEdit(Gtk::Window *parent_win, PoReader *po_reader);
		~HeaderEdit();
	private:
		PoReader  			*m_po_reader;
		guint      			m_row;
		Gtk::Table 			m_table;
		Gtk::TextView       m_txt_view;
		Gtk::ScrolledWindow m_scr_win;
		guint				m_backup_msg_no;
		Gtk::HButtonBox		m_btn_box;
		Gtk::Button			m_save_btn, m_cancel_btn;

		bool on_delete_event(GdkEventAny *event);
		void appendHeaderEntry(const Glib::ustring &header);
		void appendCommentsBox();
};

#endif /* HEADER_EDIT_H */
