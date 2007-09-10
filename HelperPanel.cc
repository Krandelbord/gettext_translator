#include "HelperPanel.h"
#define SPACING 6

HelperPanel::HelperPanel() {
	this->pack_start(m_vsep, false, false);
	this->pack_start(m_main_box, true, true, SPACING);
	this->show_all();
	
	m_main_box.pack_start(m_usage_lines, false, false, SPACING);
	m_usage_lines.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->setUsageLines("main.c:32");

	m_main_box.pack_start(m_context, false, false, SPACING);
	m_context.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->setContext("File|Open");

	m_main_box.pack_start(m_extracted_comments, false, false, SPACING);
	m_extracted_comments.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	m_extracted_comments.set_line_wrap(true);
	this->setExtractedComments("This is  good string good string good string good string");

	m_main_box.pack_start(m_comment_lb, false, false);
	m_main_box.pack_start(m_scr);
	m_scr.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_scr.add(m_comment_entry);
	m_comment_lb.set_markup("<b>Comment: </b>");
	m_comment_lb.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);

	this->show_all();
}

void HelperPanel::setUsageLines(const Glib::ustring &usage_lines) {
	m_usage_lines.set_markup("<b>Used in</b>:\n\t"+usage_lines);
}

void HelperPanel::setContext(const Glib::ustring &context) {
	m_context.set_markup("<b>Context:</b> "+context);
}

void HelperPanel::setExtractedComments(const Glib::ustring &extracted_comments) {
	m_extracted_comments.set_markup("<b>Extracted notes:</b> "+extracted_comments);
}

void HelperPanel::setComment(const Glib::ustring &comment) {
	Glib::RefPtr<Gtk::TextBuffer> buf = m_comment_entry.get_buffer();
	buf->set_text(comment);
}
