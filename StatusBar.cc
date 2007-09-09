#include "StatusBar.h"
#include <sstream>

StatusBar::StatusBar() {
	m_fuzzy_sb.set_has_resize_grip(false);
	this->pack_start(m_fuzzy_sb, true, true);

	m_untr_sb.set_has_resize_grip(false);
	this->pack_start(m_untr_sb, true, true);

	m_total_sb.set_has_resize_grip(false);
	this->pack_start(m_total_sb, true, true);

	this->setTotal(0);
	this->setCurrent(0);
	this->setFuzzy(0);
	this->setUntranslated(0);
}

void StatusBar::setTotal(size_t n) {
	std::ostringstream os;
	os << "Total" << ": " << n;
	m_total_sb.push(os.str());
}

void StatusBar::setCurrent(size_t n) {
	std::ostringstream os;
	os << "Current" << ": " << n;
	this->push(os.str());
}

void StatusBar::setFuzzy(size_t n) {
	std::ostringstream os;
	os << "Fuzzy" << ": " << n;
	m_fuzzy_sb.push(os.str());
}

void StatusBar::setUntranslated(size_t n) {
	std::ostringstream os;
	os << "Untranslated" << ": " << n;
	m_untr_sb.push(os.str());
}
