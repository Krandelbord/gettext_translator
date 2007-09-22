#include "StatusBar.h"
#include <sstream>
#include "config.h"

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
	os << _("Total") << ": " << n;
	m_total_sb.push(os.str());
}

void StatusBar::setCurrent(size_t n) {
	std::ostringstream os;
	os << _("Current") << ": " << n;
	this->push(os.str());
}

void StatusBar::setFuzzy(size_t n) {
	m_fuzzy = n;
	std::ostringstream os;
	os << _("Fuzzy") << ": " << n;
	m_fuzzy_sb.push(os.str());
}

size_t StatusBar::getFuzzy() {
	return m_fuzzy;
}

void StatusBar::setUntranslated(size_t n) {
	m_untr = n;
	std::ostringstream os;
	os << _("Untranslated") << ": " << n;
	m_untr_sb.push(os.str());
}

size_t StatusBar::getUntranslated() {
	return m_untr;
}
