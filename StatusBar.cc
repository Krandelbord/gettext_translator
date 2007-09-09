#include "StatusBar.h"

StatusBar::StatusBar() {
	m_current_sb.set_has_resize_grip(false);
	this->pack_start(m_current_sb, true, true);

	m_fuzzy_sb.set_has_resize_grip(false);
	this->pack_start(m_fuzzy_sb, true, true);

	m_untr_sb.set_has_resize_grip(false);
	this->pack_start(m_untr_sb, true, true);
}
