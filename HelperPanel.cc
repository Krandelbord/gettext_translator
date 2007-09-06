#include "HelperPanel.h"

HelperPanel::HelperPanel() {
	this->add(m_main_box);
	m_main_box.pack_start(m_vsep, false, false);
	m_main_box.add(*new Gtk::Label("Left Panel label"));
	this->show_all();
}
