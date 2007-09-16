#include "MainWindow.h"
#include "MenuBar.h"
#include "Configuration.h"
#include "TextPanel.h"
#include "Statistics.h"
#include "HelpMenu.h"
#include "Utils.h"
#include "config.h"

MainWindow::MainWindow(guint width, guint height) : m_toolbar(NULL), m_text_panel("Original text (msgid):") {
	m_po_reader = NULL;
	this->set_title(PROGRAM_NAME);
	this->set_default_size(width, height);
	this->add(m_box);

	//m_menu_bar.signal_message_changed().connect(sigc::mem_fun(this, &MainWindow::onMessageChanged));
	m_menu_bar.signal_jump_to().connect(sigc::mem_fun(this, &MainWindow::onJumpTo));
	m_menu_bar.signal_open_file().connect(sigc::mem_fun(this, &MainWindow::onOpenFile));
	Gtk::HBox *menu_box = new Gtk::HBox();
	menu_box->pack_start(m_menu_bar, false, false);
	menu_box->pack_start(*new Gtk::MenuBar(), true, true); // separator
	menu_box->pack_start(*new HelpMenu(this), false, false);

	m_box.pack_start(*menu_box, false, false);
	
	m_box.pack_start(m_toolbar, false, false);
	m_toolbar.signal_open_file().connect(sigc::mem_fun(this, &MainWindow::onOpenFile));
	m_toolbar.signal_previous_message().connect(sigc::mem_fun(this, &MainWindow::onPreviousMessage));
	m_toolbar.signal_next_message().connect(sigc::mem_fun(this, &MainWindow::onNextMessage));
	m_toolbar.signal_jump_next_message().connect(sigc::mem_fun(this, &MainWindow::onJumpNextMessage));
	m_toolbar.signal_jump_previous_message().connect(sigc::mem_fun(this, &MainWindow::onJumpPreviousMessage));
	m_toolbar.signal_language_changed().connect(sigc::mem_fun(m_tr_panel, &TranslatedTextPanel::setSpellCheck));
	m_box.pack_start(*new Gtk::HSeparator(), false, false);

	m_box.pack_start(m_hpan, true, true, 2);
	Configuration conf;
	this->show_all();
	int proc = conf.getValue("GUI", "Left pane percentage");
	int pixels = static_cast<int>(this->get_width()*proc/100.0);
	m_hpan.set_position(pixels);
	debug("Window width = %d\n", this->get_width());
	debug("Read %d%%. Setting hpane to %d pixels\n",proc, pixels);
	m_hpan.signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onPanedChaged));
	m_hpan.pack1(m_vpan);
	m_hpan.pack2(m_helper_panel);

	m_vpan.pack1(m_text_panel);
	m_tr_panel.setSpellCheck("pl");
	m_vpan.pack2(m_tr_panel);

	m_box.pack_end(m_status_bar, false, false);
	this->signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onSizeChanged));
	this->show_all();

}

void MainWindow::onFileOpened(const Glib::ustring &file_path) {
	if (m_po_reader!=NULL) delete m_po_reader;
	m_po_reader = new PoReader(file_path);
	m_toolbar.setPoReader(m_po_reader);
	
	Statistics stat(file_path);
	m_status_bar.setFuzzy(stat.getFuzzy());
	m_status_bar.setTotal(stat.getTotal());
	m_status_bar.setUntranslated(stat.getUntranslated());
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
	m_po_reader->setComments(m_helper_panel.getComment());
}

void MainWindow::fromPo2Gui() {
	m_text_panel.setText(m_po_reader->getMsgid());
	std::vector<Glib::ustring> msgstr_plurals = m_po_reader->getMsgstrPlural();
	if (msgstr_plurals.empty()) {
		m_tr_panel.setText(m_po_reader->getMsgstr(), m_po_reader->isFuzzy());
	} else {
		m_tr_panel.setText(msgstr_plurals, m_po_reader->getPluralFormsNumber());
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
	if (dialog.run()) {
		this->fromGui2Po();
		m_po_reader->jumpTo(spin->get_value());
		this->fromPo2Gui();
	}
	delete spin;
}

void MainWindow::onOpenFile() {
	Gtk::FileChooserDialog fc_dialog(*this, "open file");
	Gtk::FileFilter po_filter;
	po_filter.add_pattern("*.po");
	po_filter.add_pattern("*.pot");
	po_filter.set_name("gettext files (*.po, *.pot)");
	fc_dialog.add_filter(po_filter);

	Gtk::FileFilter all_filter;
	all_filter.add_pattern("*.*");
	all_filter.set_name("all files (*.*)");
	fc_dialog.add_filter(all_filter);

	fc_dialog.add_button(Gtk::Stock::CANCEL, 0);
	Gtk::Button *btn = fc_dialog.add_button(Gtk::Stock::OK, 1);
	fc_dialog.set_default(*btn);
	if (fc_dialog.run()) {
		this->onFileOpened(fc_dialog.get_filename());
	}
}
