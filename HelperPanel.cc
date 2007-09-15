#include "HelperPanel.h"
#include <sstream>
#define SPACING 6
using namespace Glib;
using namespace std;

HelperPanel::HelperPanel() {
	this->pack_start(m_vsep, false, false);
	this->pack_start(m_main_box, true, true, SPACING);
	this->show_all();
	
	m_main_box.pack_start(m_usage_lines, false, false, SPACING);
	m_usage_lines.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	m_usage_lines.set_markup("<b>Used in</b>:");
	m_usage_scr.add(m_usage_lines_content);
	m_usage_scr.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_usage_lines_content.set_sensitive(false);
	m_main_box.pack_start(m_usage_scr, false, false);

	m_main_box.pack_start(m_context, false, false, SPACING);
	m_context.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	this->setContext("");

	m_main_box.pack_start(m_extracted_comments, false, false, SPACING);
	m_extracted_comments.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	m_extracted_comments.set_line_wrap(true);
	this->setExtractedComments("");

	m_main_box.pack_start(m_comment_lb, false, false);
	m_main_box.pack_start(m_scr);
	m_scr.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_scr.add(m_comment_entry);
	m_comment_lb.set_markup("<b>Comment: </b>");
	m_comment_lb.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);

	this->show_all();
}

void HelperPanel::setUsageLines(std::vector<Glib::ustring> usage_lines) {
	ostringstream ostr;
	for (vector<ustring>::iterator it = usage_lines.begin(); it < usage_lines.end(); ++it) {
		ostr << "\t" << *it << "\n";
	}
	Glib::RefPtr<Gtk::TextBuffer> buf = m_usage_lines_content.get_buffer();
	buf->set_text(ostr.str());
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

Glib::ustring HelperPanel::getComment() {
	Glib::RefPtr<Gtk::TextBuffer> buf = m_comment_entry.get_buffer();
	return buf->get_text();
}
