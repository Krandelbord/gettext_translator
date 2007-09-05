#include <gtkmm.h>
#include <iostream>
#include "MainWindow.h"
#include "Configuration.h"

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
}
int main(int argc, char **argv) {
	Gtk::Main app(argc, argv);
	saveDefaults();

	Glib::RefPtr<Gdk::Screen> scr = Gdk::Screen::get_default();
	int width  = scr->get_width();
	int height = scr->get_height();

	{
		Configuration conf;
		width = width*conf.getValue("GUI", "width percentage")/100.0;
		height = height*conf.getValue("GUI", "height percentage")/100.0;
	}

	MainWindow okno(width, height);
	okno.show_all();

	app.run(okno);

	return 0;
}

