#ifndef HELPER_PANEL_H
#define HELPER_PANEL_H

#include <gtkmm.h>

class HelperPanel : public Gtk::HBox {
	public:
		HelperPanel();
		void setUsageLines(const Glib::ustring &usage_lines);
		void setContext(const Glib::ustring &context);
		void setExtractedComments(const Glib::ustring &extracted_comments);
		void setComment(const Glib::ustring &comment);

	private:
		Gtk::VBox m_main_box;
		Gtk::VSeparator m_vsep;
		
		Gtk::Label m_usage_lines;
		Gtk::Label m_context;
		Gtk::Label m_extracted_comments;

		Gtk::Label m_comment_lb;
		Gtk::ScrolledWindow m_scr;
		Gtk::TextView m_comment_entry;
};

#endif /* HELPER_PANEL_H */
