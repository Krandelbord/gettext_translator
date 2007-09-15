#include "MenuBar.h"
#include "config.h"

MenuBar::MenuBar(Gtk::Window &main_win, PoReader *po_reader) {
	m_po_reader = po_reader;
	m_main_win = &main_win;
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_File", *this->createFileMenu()));
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_Edit", *this->createEditMenu()));
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_Tools", *this->createToolsMenu()));
	this->append(*new Gtk::MenuItem("Dummy", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::OPEN,  sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::SAVE) );
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::SAVE_AS) );
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	return file_menu;
}

Gtk::Menu *MenuBar::createEditMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::CUT) );
	m->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::COPY) );
	m->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::PASTE) );
	return m;
}

Gtk::Menu *MenuBar::createToolsMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::ZOOM_IN) );

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::JUMP_TO, Gtk::ICON_SIZE_MENU));
	m->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Jump to...", *img, m_signal_jump_to));
	m->items().push_back( Gtk::Menu_Helpers::MenuElem("Kill'em all", sigc::mem_fun(*this, &MenuBar::onOpenMenuitem) ) );
	return m;
}

void MenuBar::onQuitMenuitem() {
	Gtk::Main::quit();
}

void MenuBar::onOpenMenuitem() {
	Gtk::FileChooserDialog fc_dialog(*m_main_win, "open file");
	fc_dialog.run();
}

void MenuBar::setPoReader(PoReader *po_reader) {
	m_po_reader = po_reader;
}


sigc::signal<void> &MenuBar::signal_jump_to() {
	return m_signal_jump_to;
}
