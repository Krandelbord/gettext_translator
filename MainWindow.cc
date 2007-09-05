#include "MainWindow.h"
#include "Utils.h"

MainWindow::MainWindow(guint width, guint height) {
	this->set_size_request(width, height);
	this->add(m_box);

	m_tr_view.setLanguage("pl");
	m_box.add(m_tr_view);

	m_box.pack_end(m_combo, false, false);
	
	std::vector<Glib::ustring> dict_list = getDictionaryList();
	for (std::vector<Glib::ustring>::iterator it = dict_list.begin(); it != dict_list.end(); ++it) {
		m_combo.append_text(*it);
	}
	m_combo.signal_changed().connect(sigc::mem_fun(this, &MainWindow::onLanguageChanged));
	m_combo.set_active(0);
}

void MainWindow::onLanguageChanged() {
	m_tr_view.setLanguage(m_combo.get_active_text());
}
