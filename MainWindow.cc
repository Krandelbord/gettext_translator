#include "MainWindow.h"
#include "MenuBar.h"
#include "Configuration.h"
#include "TextPanel.h"
#include "Statistics.h"
#include "HelpMenu.h"
#include "Utils.h"
#include "HeaderEdit.h"
#include "config.h"

MainWindow::MainWindow(guint width, guint height) : m_text_panel(_("Original text (msgid):")) {
	m_po_reader = NULL;
	this->set_title(PROGRAM_NAME);
	this->set_default_size(width, height);
	this->add(m_box);

	m_menu_bar.disable_elements(); // disable elements that operate on m_po_reader. Because we have m_po_reader == NULL
	m_menu_bar.signal_jump_to().connect(sigc::mem_fun(this, &MainWindow::onJumpTo));
	m_menu_bar.signal_open_file().connect(sigc::mem_fun(this, &MainWindow::onOpenFile));
	m_menu_bar.signal_save().connect(sigc::mem_fun(this, &MainWindow::onSaveFile));
	m_menu_bar.signal_save_as().connect(sigc::mem_fun(this, &MainWindow::onSaveFile));
	m_menu_bar.signal_header_edit().connect(sigc::mem_fun(this, &MainWindow::onHeaderEdit));
	m_menu_bar.signal_switch_fuzzy().connect(sigc::mem_fun(this, &MainWindow::onSwitchFuzzy));
	m_menu_bar.signal_prev_msg().connect(sigc::mem_fun(this, &MainWindow::onPreviousMessage));
	m_menu_bar.signal_next_msg().connect(sigc::mem_fun(this, &MainWindow::onNextMessage));
	m_menu_bar.signal_jump_prev_msg().connect(sigc::mem_fun(this, &MainWindow::onJumpPreviousMessage));
	m_menu_bar.signal_jump_next_msg().connect(sigc::mem_fun(this, &MainWindow::onJumpNextMessage));
	m_menu_bar.signal_copy_msgid().connect(sigc::mem_fun(this, &MainWindow::onCopyMsgid));
	m_menu_bar.signal_search().connect(sigc::mem_fun(this, &MainWindow::onSearch));
	Gtk::HBox *menu_box = new Gtk::HBox();
	menu_box->pack_start(m_menu_bar, false, false);
	menu_box->pack_start(*new Gtk::MenuBar(), true, true); // separator
	menu_box->pack_start(*new HelpMenu(this), false, false);

	m_box.pack_start(*menu_box, false, false);
	
	m_box.pack_start(m_toolbar, false, false);
	m_toolbar.disable_items();
	m_toolbar.signal_open_file().connect(sigc::mem_fun(this, &MainWindow::onOpenFile));
	m_toolbar.signal_previous_message().connect(sigc::mem_fun(this, &MainWindow::onPreviousMessage));
	m_toolbar.signal_next_message().connect(sigc::mem_fun(this, &MainWindow::onNextMessage));
	m_toolbar.signal_jump_next_message().connect(sigc::mem_fun(this, &MainWindow::onJumpNextMessage));
	m_toolbar.signal_jump_previous_message().connect(sigc::mem_fun(this, &MainWindow::onJumpPreviousMessage));
	m_toolbar.signal_language_changed().connect(sigc::mem_fun(m_tr_panel, &TranslatedTextPanel::setSpellCheck));
	m_toolbar.signal_save_file().connect(sigc::mem_fun(this, &MainWindow::onSaveFile));
	m_toolbar.signal_search().connect(sigc::mem_fun(this, &MainWindow::onSearch));
	m_box.pack_start(*new Gtk::HSeparator(), false, false);

	m_box.pack_start(m_hpan, true, true, 2);
	Configuration conf;
	int proc = conf.getValue("GUI", "Left pane percentage");
	int pixels = static_cast<int>(this->get_width()*proc/100.0);
	m_hpan.set_position(pixels);
	debug("Window width = %d\n", this->get_width());
	debug("Read %d%%. Setting hpane to %d pixels\n",proc, pixels);
	m_hpan.signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onPanedChaged));
	m_hpan.pack1(m_vpan);
	m_hpan.pack2(m_helper_panel);

	Gtk::ScrolledWindow *scr_win = new Gtk::ScrolledWindow();
	scr_win->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scr_win->add(m_text_panel);
	m_vpan.pack1(*scr_win);
	m_tr_panel.setSpellCheck("pl");
	m_vpan.pack2(m_tr_panel);

	m_box.pack_end(m_status_bar, false, false);
	this->signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onSizeChanged));
}

void MainWindow::onFileOpened(const Glib::ustring &file_path) {
	if (Glib::file_test(file_path, Glib::FILE_TEST_IS_DIR)) return;

	if (m_po_reader!=NULL) delete m_po_reader;
	m_po_reader = new PoReader(file_path);
	
	m_menu_bar.enable_elements();
	m_toolbar.enable_items();

	Statistics stat(file_path);
	m_status_bar.setFuzzy(stat.getFuzzy());
	m_status_bar.setTotal(stat.getTotal());
	m_status_bar.setUntranslated(stat.getUntranslated());
	this->onNextMessage(); //to skip message nr 0
}

void MainWindow::onSizeChanged(Gtk::Requisition *r) {
	Configuration conf;
	
	Glib::RefPtr<Gdk::Screen> scr = Gdk::Screen::get_default();
	int width  = scr->get_width();
	int height = scr->get_height();

	width = this->get_width()*100.0/width;
	height = this->get_height()*100.0/height;
	if (width > 0)  conf.setValue("GUI", "width percentage", width);
	if (height > 0) conf.setValue("GUI", "height percentage", height);
}

void MainWindow::onPanedChaged(Gtk::Requisition *r) {
	Configuration conf;
	
	int proc = static_cast<int>(m_hpan.property_position()*100.0)/(this->get_width()*1.0);
	if (proc>0) 
		conf.setValue("GUI", "Left pane percentage", proc );
}

void MainWindow::fromGui2Po() {
	if (m_po_reader->getMessageNumber()<=0) return;

	if (m_po_reader->getMsgstrPlural().size()>0) {
		m_po_reader->setMsgstrPlural( m_tr_panel.getPluralTexts() );
	} else {
		m_po_reader->setMsgstr(replaceAllReturn(m_tr_panel.getText(), "\\n\n", "\n"));
	}
	
	if (m_po_reader->isFuzzy() && m_tr_panel.getFuzzy()==false) {
		m_status_bar.setFuzzy(m_status_bar.getFuzzy()-1);
	}
	if (!m_po_reader->isFuzzy() && m_tr_panel.getFuzzy()==true) {
		m_status_bar.setFuzzy(m_status_bar.getFuzzy()+1);
	}

	m_po_reader->setComments(m_helper_panel.getComment());
	m_po_reader->setFuzzy(m_tr_panel.getFuzzy());
}

void MainWindow::fromPo2Gui() {
	m_text_panel.setText(m_po_reader->getMsgid());
	std::vector<Glib::ustring> msgstr_plurals = m_po_reader->getMsgstrPlural();
	if (msgstr_plurals.empty()) {
		m_tr_panel.setText(m_po_reader->getMsgstr(), m_po_reader->isFuzzy());
	} else {
		m_tr_panel.setText(msgstr_plurals, m_po_reader->getPluralFormsNumber(), m_po_reader->isFuzzy());
	}

	m_status_bar.setCurrent(m_po_reader->getMessageNumber());
	m_helper_panel.setUsageLines(m_po_reader->getFilesUsage());
	m_helper_panel.setContext(m_po_reader->getMsgctx());
	m_helper_panel.setExtractedComments(m_po_reader->getExtractedComments());
	m_helper_panel.setComment(m_po_reader->getComments());

}

void MainWindow::onNextMessage() {
	this->fromGui2Po();
	m_po_reader->nextMessage();
	this->fromPo2Gui();
}

void MainWindow::onPreviousMessage() {
	this->fromGui2Po();
	if (m_po_reader->previousMessage()) {
		this->fromPo2Gui();
	}
	//TODO: some rollback
}

void MainWindow::onJumpNextMessage() {
	this->fromGui2Po();
	do {
		bool not_end = m_po_reader->nextMessage();
		if (!not_end) break;
	} while (!m_po_reader->isFuzzy() && m_po_reader->isTranslated());
	this->fromPo2Gui();
}

void MainWindow::onJumpPreviousMessage() {
	this->fromGui2Po();
	do {
		bool not_end = m_po_reader->previousMessage();
		if (!not_end) break;
	} while (!m_po_reader->isFuzzy() && m_po_reader->isTranslated());
	this->fromPo2Gui();
}

void MainWindow::onJumpTo() {
	Gtk::Dialog dialog;
	dialog.set_transient_for(*this);
	Gtk::SpinButton *spin = new Gtk::SpinButton(3, 0);
	spin->set_range(1, 1233); // TODO: enter max numer for file
	spin->set_increments(1, 10);
	Gtk::VBox *box = dialog.get_vbox();
	//box->pack_start(Gtk::manage(*new Gtk::Label("Enter message number")));
	box->pack_start(*spin, true, true, 5);
	dialog.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *btn = dialog.add_button(Gtk::Stock::OK, 1); 
	dialog.set_default(*btn);
	dialog.show_all();
	if (dialog.run()==1) {
		this->fromGui2Po();
		m_po_reader->jumpTo(spin->get_value());
		this->fromPo2Gui();
	}
	delete spin;
}

void MainWindow::onOpenFile() {
	Gtk::FileChooserDialog fc_dialog(*this, _("Open file"));
	Gtk::FileFilter po_filter;
	po_filter.add_pattern("*.po");
	po_filter.add_pattern("*.pot");
	po_filter.set_name(_("gettext files (*.po, *.pot)"));
	fc_dialog.add_filter(po_filter);

	Gtk::FileFilter all_filter;
	all_filter.add_pattern("*.*");
	all_filter.set_name(_("all files (*.*)"));
	fc_dialog.add_filter(all_filter);

	fc_dialog.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *btn = fc_dialog.add_button(Gtk::Stock::OK, 1);
	fc_dialog.set_default(*btn);
	if (fc_dialog.run()==1) {
		this->onFileOpened(fc_dialog.get_filename());
	}
}

void MainWindow::onSaveFile() {
	this->fromGui2Po();
	m_po_reader->setHeader("X-Generator", PROGRAM_NAME" "PROGRAM_VERSION);
	time_t t = time(NULL);
	struct tm *tmp;
	tmp = localtime(&t);
	char buf[BUFSIZ];
	strftime(buf, BUFSIZ, "%Y-%m-%d %H:%M%z", tmp);
	m_po_reader->setHeader("PO-Revision-Date", buf);
	Gtk::FileChooserDialog save_dialog(*this, _("Save file"), Gtk::FILE_CHOOSER_ACTION_SAVE);
	save_dialog.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *save_btn = save_dialog.add_button(Gtk::Stock::SAVE, 1);
	save_dialog.set_default(*save_btn);

	if (save_dialog.run()==1) m_po_reader->saveToFile(save_dialog.get_filename());
	delete save_btn;
}

void MainWindow::onHeaderEdit() {
	HeaderEdit *he = new HeaderEdit(this, m_po_reader);
	he->show_all();
}

bool MainWindow::on_delete_event(GdkEventAny *event) {
	Glib::RefPtr<Gdk::Window> gdk_win = this->get_window();
	int x, y;
	gdk_win->get_origin(x, y);
	Configuration conf;
	conf.setValue("GUI", "default window x-position", x);
	conf.setValue("GUI", "default window y-position", y);
	return false;
}

void MainWindow::onCopyMsgid() {
	if ( (m_po_reader->getMsgstrPlural()).empty() ) {
		m_tr_panel.setText(m_po_reader->getMsgid(), true);
	} else {
		std::vector<Glib::ustring> msgs;
		for (guint i=0; i < m_po_reader->getPluralFormsNumber(); ++i) {
			msgs.push_back(m_po_reader->getMsgid());
		}
		m_tr_panel.setText(msgs, m_po_reader->getPluralFormsNumber(), true);
	}
}

void MainWindow::onSwitchFuzzy() {
	m_tr_panel.setFuzzy(!m_tr_panel.getFuzzy());
}

void MainWindow::onSearch() {
	debug("On search\n");
	Gtk::Dialog dial;
	dial.set_transient_for(*this);
	
	Gtk::HBox *hbox = Gtk::manage(new Gtk::HBox());
	Gtk::Label *lb = Gtk::manage(new Gtk::Label(_("Search For")));
	Gtk::Entry *entry = Gtk::manage(new Gtk::Entry());
	hbox->pack_start(*lb);
	hbox->pack_start(*entry, true, true, 5);

	Gtk::HButtonBox *btn_box = new Gtk::HButtonBox();
	Gtk::CheckButton *in_msgstr = Gtk::manage(new Gtk::CheckButton(_("Search in msgstr")));
	in_msgstr->set_active(true);
	Gtk::CheckButton *in_msgid = Gtk::manage(new Gtk::CheckButton(_("Search in msgid")));
	Gtk::CheckButton *ignore_case = Gtk::manage(new Gtk::CheckButton(_("Ignore case")));
	btn_box->add(*in_msgstr);
	btn_box->add(*in_msgid);
	btn_box->add(*ignore_case);

	Gtk::VBox *box = dial.get_vbox();
	box->pack_start(*hbox);
	box->pack_start(*btn_box);
	box->show_all();

	dial.add_button(Gtk::Stock::CANCEL, 0);
	dial.add_button(Gtk::Stock::FIND, 1);

	if (dial.run()==1) {
		debug("Searching...\n");
		size_t backup_pos = m_po_reader->getMessageNumber();
		bool found = false;
		do {
			debug("Porownywanie %s do %s\n", entry->get_text().c_str(), m_po_reader->getMsgstr().c_str());
			if (in_msgstr->get_active() && m_po_reader->getMsgstr().find(entry->get_text())!=Glib::ustring::npos) found = true;
			if (in_msgstr->get_active() && !m_po_reader->getMsgstrPlural().empty()) {
				MsgContainer msgs = m_po_reader->getMsgstrPlural();
				for (MsgContainer::iterator it = msgs.begin(); it!=msgs.end(); ++it) {
					Glib::ustring msgstr = *it;
					if (msgstr.find(entry->get_text())!=Glib::ustring::npos) found = true;
				}
			}
			if (in_msgid->get_active()  && m_po_reader->getMsgid().find(entry->get_text())!=Glib::ustring::npos) found = true;
		} while (m_po_reader->nextMessage() && !found);
		
		if (!found) {
			m_po_reader->jumpTo(backup_pos);
			debug("Nothing found \n");
		} else {
			debug("Znaleziono\n");
			m_po_reader->previousMessage();
			this->fromPo2Gui();
			//this->onJumpTo(m_po_reader->getMessageNumber());
		}

	}
	delete hbox;
	delete btn_box;
}
