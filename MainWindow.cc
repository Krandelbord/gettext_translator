#include <sstream>
#include "MainWindow.h"
#include "MenuBar.h"
#include "Configuration.h"
#include "TextPanel.h"
#include "Statistics.h"
#include "HelpMenu.h"
#include "Utils.h"
#include "HeaderEdit.h"
#include "config.h"

extern Glib::ustring global_error_msg;

MainWindow::MainWindow(guint width, guint height) : m_text_panel(_("Original text (msgid):")) {
	m_search_msgstr = true;
	m_search_msgid = false;
	m_search_ignore_case = true;
	m_msg_count = 0;
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
	m_menu_bar.signal_search_next().connect( sigc::hide_return(sigc::mem_fun(this, &MainWindow::searchExec)) );
	m_menu_bar.signal_search_and_replace().connect(sigc::mem_fun(this, &MainWindow::onReplace));
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
	try {
		m_po_reader = new PoReader(file_path);

		m_menu_bar.enable_elements();
		m_toolbar.enable_items();

		Statistics stat(file_path);
		m_status_bar.setFuzzy(stat.getFuzzy());
		m_msg_count = stat.getTotal();
		m_status_bar.setTotal(m_msg_count);
		m_status_bar.setUntranslated(stat.getUntranslated());
		this->onNextMessage(); //to skip message nr 0
	} catch (std::exception e) {
		Gtk::Dialog dialog(_("Error when opening file"));
		dialog.set_transient_for(*this);
		Gtk::VBox *box = dialog.get_vbox();
		Gtk::HBox intern_box;
		Gtk::Label *title_lb = Gtk::manage(new Gtk::Label("<b>Error when opening file</b>"));
		title_lb->set_use_markup(true);
		box->pack_start(*title_lb);
		box->pack_start(intern_box);
		intern_box.pack_start(*Gtk::manage(new Gtk::Image(Gtk::Stock::DIALOG_ERROR, Gtk::ICON_SIZE_DIALOG)) );
		Gtk::Label *lb = Gtk::manage(new Gtk::Label(global_error_msg));
		lb->set_use_markup(true);
		intern_box.pack_start(*lb, false, false, 5);

		dialog.add_button(Gtk::Stock::CLOSE, 0);
		dialog.show_all();
		dialog.run();
	}
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
	spin->set_range(1, m_msg_count);
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
	all_filter.add_pattern("*");
	all_filter.set_name(_("all files "));
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

/**
 * @returns true if semotinhg was found
 */
bool MainWindow::searchExec() {
	debug("Searching...\n");
	size_t backup_pos = m_po_reader->getMessageNumber();
	m_po_reader->nextMessage(); // we don't wan't to search in current message
	bool found = false;
	do {
		debug("Comparing %s do %s\n", m_last_search.c_str(), m_po_reader->getMsgstr().c_str());
		if (m_search_msgstr) {
			if (m_search_ignore_case) {
				if ( IcaseCompare(m_po_reader->getMsgstr(), m_last_search) ) found = true;
			} else {
				if (compare(m_po_reader->getMsgstr(), m_last_search )) found = true;
			}
		}
		if (m_search_msgstr && !m_po_reader->getMsgstrPlural().empty()) {
			MsgContainer msgs = m_po_reader->getMsgstrPlural();
			for (MsgContainer::iterator it = msgs.begin(); it!=msgs.end(); ++it) {
				Glib::ustring msgstr = *it;
				if (m_search_ignore_case) {
					if ( IcaseCompare(msgstr, m_last_search) ) found = true;
				} else {
					if (compare(msgstr, m_last_search) ) found = true;
				}
			}
		}
		if (m_search_msgid) {
			if (m_search_ignore_case) {
				if (IcaseCompare(m_po_reader->getMsgid(), m_last_search) ) found = true;
			} else {
				if (compare(m_po_reader->getMsgid(), m_last_search) ) found = true;
			}
		}
	} while (m_po_reader->nextMessage() && !found);

	if (!found) {
		debug("Nothing found \n");
		m_po_reader->jumpTo(backup_pos);
		return false;
	} else {
		debug("Found\n");
		m_po_reader->previousMessage();
		this->fromPo2Gui();
		return true;
	}

}

void MainWindow::onSearch() {
	debug("On search\n");
	Gtk::Dialog dial;
	dial.set_title(_("Search"));
	dial.set_transient_for(*this);
	
	Gtk::HBox *hbox = Gtk::manage(new Gtk::HBox());
	Gtk::Label *lb = Gtk::manage(new Gtk::Label(_("Search For")));
	Gtk::Entry *entry = Gtk::manage(new Gtk::Entry());
	if (m_last_search.length() > 0) entry->set_text(m_last_search);
	entry->set_activates_default(true);
	hbox->pack_start(*lb);
	hbox->pack_start(*entry, true, true, 5);

	Gtk::HButtonBox *btn_box = new Gtk::HButtonBox();
	Gtk::CheckButton *in_msgstr = Gtk::manage(new Gtk::CheckButton(_("Search in msgstr")));
	in_msgstr->set_active(m_search_msgstr);
	Gtk::CheckButton *in_msgid = Gtk::manage(new Gtk::CheckButton(_("Search in msgid")));
	in_msgid->set_active(m_search_msgid);
	Gtk::CheckButton *ignore_case = Gtk::manage(new Gtk::CheckButton(_("Ignore case")));
	ignore_case->set_active(m_search_ignore_case);
	btn_box->add(*in_msgstr);
	btn_box->add(*in_msgid);
	btn_box->add(*ignore_case);

	Gtk::VBox *box = dial.get_vbox();
	box->pack_start(*hbox);
	box->pack_start(*btn_box);
	box->show_all();

	dial.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *find_btn = dial.add_button(Gtk::Stock::FIND, 1);
	dial.set_default(*find_btn);

	if (dial.run()==1) {
		m_search_ignore_case = ignore_case->get_active();
		m_search_msgid = in_msgid->get_active();
		m_search_msgstr = in_msgstr->get_active();
		m_last_search = entry->get_text();
		searchExec();	
	}
	delete hbox;
	delete btn_box;
}

void MainWindow::onReplace() {
	Gtk::Dialog dial;
	dial.set_title(_("Search and replace"));
	dial.set_transient_for(*this);
	
	Gtk::Table *tab = Gtk::manage(new Gtk::Table());
	Gtk::Label *lb = Gtk::manage(new Gtk::Label(_("Search in translated messages for")));
	Gtk::Entry *entry = Gtk::manage(new Gtk::Entry());
	if (m_last_search.length() > 0) entry->set_text(m_last_search);
	entry->set_activates_default(true);
	tab->attach(*lb, 0, 1, 0, 1);
	tab->attach(*entry, 1, 2, 0, 1, Gtk::FILL, Gtk::FILL, 5, 5);

	Gtk::Label *lb_rp = Gtk::manage(new Gtk::Label(_("Replace with")));
	Gtk::Entry *entry_rp = Gtk::manage(new Gtk::Entry());
	if (m_last_replace.length() > 0) entry_rp->set_text(m_last_replace);
	entry_rp->set_activates_default(true);
	tab->attach(*lb_rp, 0, 1, 1, 2);
	tab->attach(*entry_rp, 1, 2, 1, 2, Gtk::FILL, Gtk::FILL, 5, 5);


	Gtk::HButtonBox *btn_box = new Gtk::HButtonBox();
	Gtk::CheckButton *replace_all = Gtk::manage(new Gtk::CheckButton(_("Replace all")));
	replace_all->set_active(false);
	btn_box->add(*replace_all);

	Gtk::VBox *box = dial.get_vbox();
	box->pack_start(*tab);
	box->pack_start(*btn_box);
	box->show_all();

	dial.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *find_btn = dial.add_button(Gtk::Stock::FIND_AND_REPLACE, 1);
	dial.set_default(*find_btn);

	size_t replace_count = 0;
	if (dial.run()==1) {
		m_last_search = entry->get_text();
		m_last_replace = entry_rp->get_text();

		// backup search options
		bool tmp_ignore_case = m_search_ignore_case;
		m_search_ignore_case = false;
		bool tmp_search_msgid = m_search_msgid;
		m_search_msgid = false;
		bool tmp_search_msgstr = m_search_msgstr;
		m_search_msgstr = true;

		// If we dont find string in current message search for a first one
		if (!doReplace(m_last_search, m_last_replace)) {
			if (searchExec()) {
				doReplace(m_last_search, m_last_replace);
				replace_count++;
			}
		}
		if (replace_all->get_active()) {
			while (searchExec()) {
				doReplace(m_last_search, m_last_replace);
				replace_count++;
			}
		}
		m_search_ignore_case = tmp_ignore_case;
		m_search_msgstr = tmp_search_msgstr;
		m_search_msgid = tmp_search_msgid;
	}
	
	if (replace_all->get_active()) {
		Gtk::Dialog dial_sum;
		dial_sum.set_title(_("Search and replace - summary"));
		dial_sum.set_transient_for(*this);
		box = dial_sum.get_vbox();
		Gtk::Label *lb_title = Gtk::manage(new Gtk::Label(_("<b>Search And Replace Summary</b>")));
		lb_title->set_use_markup(true);
		box->pack_start(*lb_title);
		Gtk::HBox *hbox = Gtk::manage(new Gtk::HBox());
		box->pack_start(*hbox);

		Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::DIALOG_INFO, Gtk::ICON_SIZE_DIALOG));
		hbox->pack_start(*img);
		std::ostringstream ss;
		ss << replace_count << " " << ngettext("message modified", "messages modified", replace_count);
		Gtk::Label *lbsum = Gtk::manage(new Gtk::Label(ss.str()));
		hbox->pack_start(*lbsum);
		box->show_all();
		dial_sum.add_button(Gtk::Stock::CLOSE, 0);
		dial_sum.run();
		delete lb_title;
		delete hbox;
	}

	delete tab;
	delete btn_box;
}

/**
 * @returns if replace was made
 */
bool MainWindow::doReplace(const Glib::ustring &str1, const Glib::ustring &str2) {
	if (m_tr_panel.getPluralTexts().empty()) {
		Glib::ustring msgstr = m_tr_panel.getText();
		size_t string_pos = msgstr.find(str1);
		if (string_pos!=Glib::ustring::npos) {
			msgstr.replace( string_pos, msgstr.length(), str2);
			m_tr_panel.setText(msgstr, m_tr_panel.getFuzzy());
			return true;
		}
		return false;
	} else {
		bool replaced = false;
		MsgContainer msgs = m_tr_panel.getPluralTexts();
		MsgContainer new_msgstr;
		for (MsgContainer::iterator it = msgs.begin(); it!=msgs.end(); ++it) {
			Glib::ustring msgstr = *it;
			size_t string_pos = msgstr.find(str1);
			if (string_pos!=Glib::ustring::npos) {
				msgstr.replace( string_pos, msgstr.length(), str2);
				replaced = true;
			}
			new_msgstr.push_back(msgstr);
		}
		m_tr_panel.setText(new_msgstr, m_po_reader->getPluralFormsNumber(), m_tr_panel.getFuzzy());
		return replaced;
	}
}
