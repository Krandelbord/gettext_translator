#include "HelpMenu.h"
#include <sstream>
#include <gettext-po.h>
#include "config.h"

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

	this->items().push_back(Menu_Helpers::MenuElem(_("_Help"), *help_content_menu));
}

void HelpMenu::onAbout(Window *main_win) {
	AboutDialog about;
	about.set_transient_for(*main_win);
	about.set_copyright("GNU GPL 2");

	std::list<Glib::ustring> authors;
	authors.push_back("Author: Emil Nowak <emiml@wp.pl>");
	about.set_authors(authors);
	
	about.set_version(PROGRAM_VERSION);

	about.set_translator_credits(_("Translator credits"));

	std::ostringstream os;
	int v = libgettextpo_version;
	os << _("Used libraries:") << std::endl;
	os << _("libGettext-po version ");
	os << (v>>16) << "." << (v>>8) << "." << (v-v>>8-v>>16) << std::endl; 
	
	os << _("Gtkmm version ") << GTKMM_MAJOR_VERSION;
	os << "." << GTKMM_MINOR_VERSION << "." <<  GTKMM_MICRO_VERSION << std::endl;

	about.set_comments(os.str());

	about.run();
}
