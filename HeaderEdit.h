#ifndef HEADER_EDIT_H
#define HEADER_EDIT_H

#include <gtkmm.h>

class HeaderEdit : public Gtk::Window {
	public:
		HeaderEdit();
		~HeaderEdit();
	private:
		bool on_delete_event(GdkEventAny *event);
};

#endif /* HEADER_EDIT_H */
