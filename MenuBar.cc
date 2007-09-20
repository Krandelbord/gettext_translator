#include "MenuBar.h"
#include "config.h"

MenuBar::MenuBar() {
	this->items().push_back(MenuElem("_File", *this->createFileMenu()));
	this->items().push_back(MenuElem("_Edit", *this->createEditMenu()));
	this->items().push_back(MenuElem("_Tools", *this->createToolsMenu()));
	this->append(*new Gtk::MenuItem("Dummy", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	StockMenuElem *m = new StockMenuElem(Gtk::Stock::OPEN, Gtk::AccelKey("<Control>O"), m_signal_open_file);
	disable_list.push_back(m);
	file_menu->items().push_back(*m);
	file_menu->items().push_back( StockMenuElem(Gtk::Stock::OPEN, Gtk::AccelKey("<Control>O"), m_signal_open_file) );
	file_menu->items().push_back( StockMenuElem(Gtk::Stock::SAVE, Gtk::AccelKey("<Control>S"), m_signal_save) );
	file_menu->items().push_back( StockMenuElem(Gtk::Stock::SAVE_AS, Gtk::AccelKey("<Shift><Control>S"), m_signal_save_as) );
	file_menu->items().push_back( StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	this->disable_elements();
	return file_menu;
}

Gtk::Menu *MenuBar::createEditMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( StockMenuElem(Gtk::Stock::CUT) );
	m->items().push_back( StockMenuElem(Gtk::Stock::COPY) );
	m->items().push_back( StockMenuElem(Gtk::Stock::PASTE) );

	m->items().push_back( SeparatorElem());

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU));
	m->items().push_back(ImageMenuElem("Edit Headers...", *img, m_signal_header_edit));

	m->items().push_back(MenuElem("Toggle Fuzzy", Gtk::AccelKey("<control>U"), m_signal_switch_fuzzy));
	return m;
}

Gtk::Menu *MenuBar::createToolsMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( StockMenuElem(Gtk::Stock::ZOOM_IN) );

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::JUMP_TO, Gtk::ICON_SIZE_MENU));
	m->items().push_back(ImageMenuElem("Jump to...", Gtk::AccelKey("<Control>G"), *img, m_signal_jump_to));
	m->items().push_back( MenuElem("Kill'em all", sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	m->items().push_back(MenuElem("Copy original message to translation", Gtk::AccelKey("<Control>space"), m_signal_copy_msgid));

	m->items().push_back(MenuElem("Previous Message", Gtk::AccelKey("Page_Up"), m_signal_prev_msg));
	m->items().push_back(MenuElem("Next Message", Gtk::AccelKey("Page_Down"), m_signal_next_msg));

	m->items().push_back(MenuElem("Jump to previous message", Gtk::AccelKey("<Control>Page_Up"), m_signal_jump_prev_msg));
	m->items().push_back(MenuElem("Jump to next message", Gtk::AccelKey("<Control>Page_Down"), m_signal_jump_next_msg));
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

sigc::signal<void> &MenuBar::signal_switch_fuzzy() {
	return m_signal_switch_fuzzy;
}

sigc::signal<void> &MenuBar::signal_next_msg() {
	return m_signal_next_msg;
}

sigc::signal<void> &MenuBar::signal_prev_msg() {
	return m_signal_prev_msg;
}

sigc::signal<void> &MenuBar::signal_jump_next_msg() {
	return m_signal_jump_next_msg;
}

sigc::signal<void> &MenuBar::signal_jump_prev_msg() {
	return m_signal_jump_prev_msg;
}

sigc::signal<void>  &MenuBar::signal_copy_msgid() {
	return m_signal_copy_msgid;
}

sigc::signal<void> &MenuBar::signal_save() {
	return m_signal_save;
}

sigc::signal<void> &MenuBar::signal_save_as() {
	return m_signal_save_as;
}

void MenuBar::disable_elements() {
	for (ElementsList::iterator it = disable_list.begin(); it!=disable_list.end(); ++it) {
		Glib::RefPtr<Gtk::MenuItem> e = (*it)->get_child();
		e->set_sensitive(false);
	}
}

void MenuBar::enable_elements() {
	for (ElementsList::iterator it = disable_list.begin(); it!=disable_list.end(); ++it) {
		Glib::RefPtr<Gtk::MenuItem> e = (*it)->get_child();
		e->set_sensitive(true);
	}
}
