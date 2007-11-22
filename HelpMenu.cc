#include "HelpMenu.h"
#include <sstream>
#include <gettext-po.h>
#include "config.h"

using namespace Gtk;

HelpMenu::HelpMenu(Window *main_win) {
	Menu *help_content_menu = new Menu();
	help_content_menu->items().push_back(
			Menu_Helpers::StockMenuElem(
				Stock::HELP,
				sigc::bind<Window*>(sigc::mem_fun(this, &HelpMenu::onHelp), main_win)
				)
			);
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

void HelpMenu::onHelp(Window *main_win) {
	Dialog di;
	di.set_transient_for(*main_win);
	int w,h;
	main_win->get_size(w, h);
	di.set_default_size(w*0.5, h*0.8);
	di.set_title(_("Gettext Translator - Help"));
	Box *box = di.get_vbox();
	ScrolledWindow *sw = manage(new ScrolledWindow());
	box->pack_start(*sw);
	sw->set_policy(POLICY_AUTOMATIC, POLICY_AUTOMATIC);

	Label *lb = manage(new Gtk::Label("", ALIGN_LEFT, ALIGN_TOP));
	lb->set_use_markup(true);
	lb->set_markup(_("<b>Gettext Translator Help</b>\n\n"
				"This program should be so easy to use that you should't need manual/help.\n"
				"If you have some problems please contact author on emil5@go2.pl or jabber emil.nowak@jabber.org\n"
				"You can visit program homepage at http://emiml.pl/translator/"
				));
	lb->set_line_wrap(true);
	sw->add(*lb);
	box->show_all();
	di.add_button(Gtk::Stock::CLOSE, 0);
	di.run();
	delete sw;
}
