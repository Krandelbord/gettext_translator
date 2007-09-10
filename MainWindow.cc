#include "MainWindow.h"
#include "MenuBar.h"
#include "Configuration.h"
#include "TextPanel.h"
#include "Statistics.h"
#include "HelpMenu.h"
#include "config.h"

void MainWindow::onPanedChaged(Gtk::Requisition *r) {
	Configuration conf;
	
	int proc = static_cast<int>(m_hpan.property_position()*100.0)/(this->get_width()*1.0);
	if (proc>0) 
		conf.setValue("GUI", "Left pane percentage", proc );
}

void MainWindow::onMessageChanged() {
	debug("Message %s\n", m_po_reader->getMsgid().c_str());
	m_text_panel.setText(m_po_reader->getMsgid());
	m_tr_panel.setText(m_po_reader->getMsgstr(), m_po_reader->isFuzzy());

	m_status_bar.setCurrent(m_po_reader->getMessageNumber());
	m_helper_panel.setUsageLines(m_po_reader->getFilesUsage());
	m_helper_panel.setContext(m_po_reader->getMsgctx());
	m_helper_panel.setExtractedComments(m_po_reader->getExtractedComments());
	m_helper_panel.setComment(m_po_reader->getComments());
}

MainWindow::MainWindow(guint width, guint height) : m_toolbar(NULL), m_text_panel("Original text (msgid):") {
	m_po_reader = NULL;
	this->set_default_size(width, height);
	this->add(m_box);

	Gtk::HBox *menu_box = new Gtk::HBox();
	menu_box->pack_start(*new MenuBar(*this), false, false);
	menu_box->pack_start(*new Gtk::MenuBar(), true, true); // separator
	menu_box->pack_start(*new HelpMenu(this), false, false);

	m_box.pack_start(*menu_box, false, false);
	
	m_box.pack_start(m_toolbar, false, false);
	m_toolbar.signal_message_changed().connect(sigc::mem_fun(this, &MainWindow::onMessageChanged));
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
