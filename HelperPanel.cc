#include "HelperPanel.h"

HelperPanel::HelperPanel() {
	this->add(*new Gtk::Label("Left Panel label"));
	this->show_all();
}
