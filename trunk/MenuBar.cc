#include "MenuBar.h"
#include "config.h"

MenuBar::MenuBar() {
	this->items().push_back(MenuElem(_("_File"), *this->createFileMenu()));
	this->items().push_back(MenuElem(_("_Edit"), *this->createEditMenu()));
	this->items().push_back(MenuElem(_("_Tools"), *this->createToolsMenu()));
	//this->append(*new Gtk::MenuItem("Dummy", true));
}

Gtk::Menu *MenuBar::createFileMenu() {
	Gtk::Menu *file_menu = new Gtk::Menu();
	file_menu->items().push_back( StockMenuElem(Gtk::Stock::OPEN, Gtk::AccelKey("<Control>O"), m_signal_open_file) );

	StockMenuElem *me = new StockMenuElem(Gtk::Stock::SAVE, Gtk::AccelKey("<Control>S"), m_signal_save);
	m_disable_list.push_back(me);
	file_menu->items().push_back(*me);

	me = new StockMenuElem(Gtk::Stock::SAVE_AS, Gtk::AccelKey("<Shift><Control>S"), m_signal_save_as);
	m_disable_list.push_back(me);
	file_menu->items().push_back(*me);

	file_menu->items().push_back( StockMenuElem(Gtk::Stock::QUIT,  sigc::mem_fun(*this, &MenuBar::onQuitMenuitem) ) );
	return file_menu;
}

Gtk::Menu *MenuBar::createEditMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	m->items().push_back( StockMenuElem(Gtk::Stock::CUT) );
	m->items().push_back( StockMenuElem(Gtk::Stock::COPY) );
	m->items().push_back( StockMenuElem(Gtk::Stock::PASTE) );

	m->items().push_back( SeparatorElem());

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::FIND, Gtk::ICON_SIZE_MENU));
	Element *me = new ImageMenuElem(_("Find..."), Gtk::AccelKey("<control>F"), *img, m_signal_search);
	m_disable_list.push_back(me);
	m->items().push_back(*me);
	me = new MenuElem(_("Find Next"), Gtk::AccelKey("F3"), m_signal_search_next);
	m_disable_list.push_back(me);
	m->items().push_back(*me);
	img = Gtk::manage(new Gtk::Image(Gtk::Stock::FIND_AND_REPLACE, Gtk::ICON_SIZE_MENU)); 
	me = new ImageMenuElem(_("Find And Replace..."), Gtk::AccelKey("<control>R"), *img, m_signal_search_and_replace);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	m->items().push_back( SeparatorElem());

	img = Gtk::manage(new Gtk::Image(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU));
	me = new ImageMenuElem(_("Edit Headers..."), *img, m_signal_header_edit);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	me = new MenuElem(_("Toggle Fuzzy"), Gtk::AccelKey("<control>U"), m_signal_switch_fuzzy);
	m_disable_list.push_back(me);
	m->items().push_back(*me);
	return m;
}

Gtk::Menu *MenuBar::createToolsMenu() {
	Gtk::Menu *m = new Gtk::Menu();
	//m->items().push_back( StockMenuElem(Gtk::Stock::ZOOM_IN) );

	Gtk::Widget *img = Gtk::manage(new Gtk::Image(Gtk::Stock::JUMP_TO, Gtk::ICON_SIZE_MENU));
	Element *me = new ImageMenuElem(_("Jump to..."), Gtk::AccelKey("<Control>G"), *img, m_signal_jump_to);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	me = new MenuElem(_("Copy original message to translation"), Gtk::AccelKey("<Control>space"), m_signal_copy_msgid);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	me = new MenuElem(_("Previous Message"), Gtk::AccelKey("Page_Up"), m_signal_prev_msg);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	me = new MenuElem(_("Next Message"), Gtk::AccelKey("Page_Down"), m_signal_next_msg);
	m_disable_list.push_back(me);
	m->items().push_back(*me);

	me = new MenuElem(_("Jump to previous message"), Gtk::AccelKey("<Control>Page_Up"), m_signal_jump_prev_msg);
	m_disable_list.push_back(me);
	m->items().push_back(*me);
	
	me = new MenuElem(_("Jump to next message"), Gtk::AccelKey("<Control>Page_Down"), m_signal_jump_next_msg);
	m_disable_list.push_back(me);
	m->items().push_back(*me);
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

sigc::signal<void> &MenuBar::signal_search() {
	return m_signal_search;
}

sigc::signal<void> &MenuBar::signal_search_next() {
	return m_signal_search_next;
}

sigc::signal<void> &MenuBar::signal_search_and_replace() {
	return m_signal_search_and_replace;
}

void MenuBar::disable_elements() {
	for (ElementsList::iterator it = m_disable_list.begin(); it!=m_disable_list.end(); ++it) {
		Glib::RefPtr<Gtk::MenuItem> e = (*it)->get_child();
		e->set_sensitive(false);
	}
}

void MenuBar::enable_elements() {
	for (ElementsList::iterator it = m_disable_list.begin(); it!=m_disable_list.end(); ++it) {
		Glib::RefPtr<Gtk::MenuItem> e = (*it)->get_child();
		e->set_sensitive(true);
	}
}
