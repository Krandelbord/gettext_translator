#include <gtkmm.h>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char **argv) {
	Gtk::Main app(argc, argv);

	Gtk::VBox box;

	MainWindow okno(800, 600);

	okno.show_all();

	app.run(okno);

	//std::cout << "Lista ma rozmiar " << getDictionaryList().size() << std::endl;
	return 0;
}

