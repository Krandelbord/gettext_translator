#ifndef HELPER_PANEL_H
#define HELPER_PANEL_H

#include <gtkmm.h>
#include <vector>

class HelperPanel : public Gtk::HBox {
	public:
		HelperPanel();
		void setUsageLines(std::vector<Glib::ustring> lines);
		void setContext(const Glib::ustring &context);
		void setExtractedComments(const Glib::ustring &extracted_comments);
		void setComment(const Glib::ustring &comment);
		Glib::ustring getComment();

	private:
		Gtk::VBox m_main_box;
		Gtk::VSeparator m_vsep;
		
		Gtk::Label          m_usage_lines;	
		Gtk::ScrolledWindow m_usage_scr;
		Gtk::TextView       m_usage_lines_content;

		Gtk::Label m_context;
		Gtk::Label m_extracted_comments;

		Gtk::Label m_comment_lb;
		Gtk::ScrolledWindow m_scr;
		Gtk::TextView m_comment_entry;
};

#endif /* HELPER_PANEL_H */
