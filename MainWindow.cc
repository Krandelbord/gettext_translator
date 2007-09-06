#include "MainWindow.h"
#include "Utils.h"
#include "MenuBar.h"
#include "Configuration.h"
#include "TextPanel.h"
#include "TranslatedTextPanel.h"
#include "HelperPanel.h"
#include "config.h"

void MainWindow::onPanedChaged(Gtk::Requisition *r) {
	Configuration conf;
	
	int proc = static_cast<int>(m_hpan.property_position()*100.0)/(this->get_width()*1.0);
	if (proc>0) 
		conf.setValue("GUI", "Left pane percentage", proc );
}

MainWindow::MainWindow(guint width, guint height) {
	this->set_default_size(width, height);
	this->add(m_box);

	m_box.pack_start(*new MenuBar(*this), false, false);
	m_box.pack_start(*new Gtk::HSeparator(), false, false);

	m_box.add(m_hpan);
	Configuration conf;
	this->show_all();
	int proc = conf.getValue("GUI", "Left pane percentage");
	int pixels = static_cast<int>(this->get_width()*proc/100.0);
	m_hpan.set_position(pixels);
	debug("Window width = %d\n", this->get_width());
	debug("Read %d%%. Setting hpane to %d pixels\n",proc, pixels);
	m_hpan.signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onPanedChaged));
	m_hpan.pack1(m_vpan);
	m_hpan.pack2(*new HelperPanel());

	m_vpan.pack1(*new TextPanel("Original text (msgid):"));
	m_vpan.pack2(*new TranslatedTextPanel());

	
	std::vector<Glib::ustring> dict_list = getDictionaryList();
	/*for (std::vector<Glib::ustring>::iterator it = dict_list.begin(); it != dict_list.end(); ++it) {
		m_combo.append_text(*it);
	}
	m_combo.signal_changed().connect(sigc::mem_fun(this, &MainWindow::onLanguageChanged));
	m_combo.set_active(0);
	*/
	m_box.pack_end(*new Gtk::Statusbar(), false, false);
	this->signal_size_request().connect(sigc::mem_fun(this, &MainWindow::onSizeChanged));
	this->show_all();

}

void MainWindow::onLanguageChanged() {
	//m_tr_view.setLanguage(m_combo.get_active_text());
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
