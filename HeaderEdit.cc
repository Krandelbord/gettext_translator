#include "HeaderEdit.h"
#include "config.h"

HeaderEdit::HeaderEdit() {
}

HeaderEdit::~HeaderEdit() {
	debug("Destruktor\n");
}

bool HeaderEdit::on_delete_event(GdkEventAny *event) {
	delete this;
}
