#include "HeaderEdit.h"
#include "config.h"

HeaderEdit::HeaderEdit(Gtk::Window *parent_win, PoReader *po_reader) : 
	m_save_btn(Gtk::Stock::SAVE), 
	m_cancel_btn(Gtk::Stock::CANCEL) {

	m_po_reader = po_reader;
	m_row = 0;
	m_backup_msg_no = m_po_reader->getMessageNumber();
	this->set_transient_for(*parent_win);
	this->set_modal(true);
	this->set_border_width(5);
	this->add(m_table);

	this->appendCommentsBox();

	this->appendHeaderEntry("Report-Msgid-Bugs-To");
	this->appendHeaderEntry("Project-Id-Version");
	this->appendHeaderEntry("POT-Creation-Date");
	this->appendHeaderEntry("PO-Revision-Date");
	this->appendHeaderEntry("Last-Translator");
	this->appendHeaderEntry("Language-Team");
	this->appendHeaderEntry("MIME-Version");
	this->appendHeaderEntry("Content-Type");
	this->appendHeaderEntry("Content-Transfer-Encoding");
	this->appendHeaderEntry("Plural-Forms");
	this->appendHeaderEntry("X-Generator");

	m_table.attach(m_btn_box, 0, 2, m_row, m_row+1);
	m_row++;
	m_btn_box.pack_start(m_cancel_btn);
	m_btn_box.pack_start(m_save_btn);
	this->show_all();
}

HeaderEdit::~HeaderEdit() {
	debug("Destruktor\n");
}

bool HeaderEdit::on_delete_event(GdkEventAny *event) {
	if (m_backup_msg_no != m_po_reader->getMessageNumber()) {
		// rollback
		m_po_reader->jumpTo(m_backup_msg_no);
	}
	delete this;
	return true;
}

void HeaderEdit::appendHeaderEntry(const Glib::ustring &header) {
	Glib::ustring h_value = m_po_reader->getHeader(header);
	if (h_value.length() > 0) {
		m_table.attach(*new Gtk::Label(header), 0, 1, m_row, m_row+1, Gtk::SHRINK, Gtk::SHRINK, 5, 5);
		Gtk::Entry *entry = new Gtk::Entry();
		entry->set_text(h_value);
		m_table.attach(*entry, 1, 2, m_row, m_row+1, Gtk::FILL|Gtk::EXPAND, Gtk::SHRINK, 5, 5);
		m_row++;
	}
}

void HeaderEdit::appendCommentsBox() {
	m_po_reader->jumpTo(0);
	Glib::RefPtr<Gtk::TextBuffer> buf = m_txt_view.get_buffer();
	buf->set_text(m_po_reader->getComments());
	m_scr_win.add(m_txt_view);
	m_scr_win.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_table.attach(m_scr_win, 0, 2, m_row, m_row+1);
	m_row++;
}
