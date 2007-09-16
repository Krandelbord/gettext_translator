#include "MenuBar.h"
#include "config.h"

MenuBar::MenuBar() {
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_File", *this->createFileMenu()));
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_Edit", *this->createEditMenu()));
	this->items().push_back(Gtk::Menu_Helpers::MenuElem("_Tools", *this->createToolsMenu()));
	this->append(*new Gtk::MenuItem("Dummy", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	file_menu->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::OPEN,  m_signal_open_file) );
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

	m->items().push_back( Gtk::Menu_Helpers::SeparatorElem());

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU));
	m->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Edit Headers...", *img, m_signal_header_edit));
	return m;
}

Gtk::Menu *MenuBar::createToolsMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( Gtk::Menu_Helpers::StockMenuElem(Gtk::Stock::ZOOM_IN) );

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::JUMP_TO, Gtk::ICON_SIZE_MENU));
	m->items().push_back(Gtk::Menu_Helpers::ImageMenuElem("Jump to...", *img, m_signal_jump_to));
	m->items().push_back( Gtk::Menu_Helpers::MenuElem("Kill'em all", sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	return m;
}

void MenuBar::onQuitMenuitem() {
	Gtk::Main::quit();
}

sigc::signal<void> &MenuBar::signal_jump_to() {
	return m_signal_jump_to;
}

sigc::signal<void> &MenuBar::signal_open_file() {
	return m_signal_open_file;
}

sigc::signal<void> &MenuBar::signal_header_edit() {
	return m_signal_header_edit;
}
