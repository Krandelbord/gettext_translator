#include "HelpMenu.h"
using namespace Gtk;

HelpMenu::HelpMenu(Window *main_win) {
	Menu *help_content_menu = new Menu();
	help_content_menu->items().push_back(Menu_Helpers::StockMenuElem(Stock::HELP));
	help_content_menu->items().push_back(
			Menu_Helpers::StockMenuElem(
				Stock::ABOUT, 
				sigc::bind<Window*>(sigc::mem_fun(this, &HelpMenu::onAbout), main_win) 
				)
			);

	this->items().push_back(Menu_Helpers::MenuElem("_Help", *help_content_menu));
}

void HelpMenu::onAbout(Window *main_win) {
	AboutDialog about;
	about.set_transient_for(*main_win);
	about.set_copyright("GNU GPL 2");
	
	std::list<Glib::ustring> authors;
	authors.push_back("Author: Emil Nowak <emiml@wp.pl>");
	about.set_authors(authors);

	about.set_translator_credits("");
	about.set_version("0.01 alpha");

	about.run();
}
