#include <gtkmm.h>
#include "MainWindow.h"
#include "Configuration.h"
#include "config.h"

bool GLOBAL_ERROR_OCCURED;
Glib::ustring global_error_msg;

void saveDefaults() {
	Configuration conf;

	if (conf.getValue("GUI", "width percentage") <= 0) {
		conf.setValue("GUI", "width percentage", 70);
	}
	if (conf.getValue("GUI", "height percentage") <= 0) {
		conf.setValue("GUI", "height percentage", 80);
	}

	if (conf.getValue("GUI", "Left pane percentage") <= 0) {
		conf.setValue("GUI", "Left pane percentage", 82);
	}

	if (conf.getValue("GUI", "default window x-position") <= 0) {
		conf.setValue("GUI", "default window x-position", 1);
		conf.setValue("GUI", "default window y-position", 1);
	}
}
int main(int argc, char **argv) {
	GLOBAL_ERROR_OCCURED=false;

	bindtextdomain(PACKAGE, GETTEXT_PATH);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain(PACKAGE);

	Glib::set_application_name(PROGRAM_NAME);

	Glib::OptionContext context(_("<some_file.po>"));
	context.set_translation_domain(PACKAGE);
	context.parse(argc, argv);

	Gtk::Main app(argc, argv);
	saveDefaults();

	Glib::RefPtr<Gdk::Screen> scr = Gdk::Screen::get_default();
	int width  = scr->get_width();
	int height = scr->get_height();

	int x, y;
	{
		Configuration conf;
		width = width*conf.getValue("GUI", "width percentage")/100.0;
		height = height*conf.getValue("GUI", "height percentage")/100.0;
		x = conf.getValue("GUI", "default window x-position");
		y = conf.getValue("GUI", "default window y-position");
	}

	MainWindow okno(width, height);
	okno.move(x, y);
	okno.show_all();

	if (argc>1) {
		if (Glib::file_test(argv[1], Glib::FILE_TEST_EXISTS)) {
			okno.onFileOpened(argv[1]);
		}
	}

	app.run(okno);

	return 0;
}

