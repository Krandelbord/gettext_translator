#include "config.h"

#include "Configuration.h"
#include <glibmm.h>

Configuration::Configuration() {
	m_key_file = g_key_file_new();
	
	const gchar *konf_rootdir = g_get_user_config_dir();
	m_file = g_build_filename(konf_rootdir, "gettext_translator.cfg", NULL);
	g_key_file_load_from_file(m_key_file, m_file, G_KEY_FILE_KEEP_COMMENTS, NULL);
}

int Configuration::getValue(const Glib::ustring &category, const Glib::ustring &name) const {
	debug("\033[1;31m Getting value \033[1;0m = %s / %s = %d\n", 
			category.c_str(), name.c_str(), 
			g_key_file_get_integer(m_key_file, category.c_str(), name.c_str(), NULL));

	return g_key_file_get_integer(m_key_file, category.c_str(), name.c_str(), NULL);
}

void Configuration::setValue(const Glib::ustring &category, const Glib::ustring &name, int value) {
	debug("\033[1;32m Setting \033[1;0m value = %s / %s = %d\n", category.c_str(), name.c_str(), value);
	g_key_file_set_integer(m_key_file, category.c_str(), name.c_str(), value);
}

Configuration::~Configuration() {
	GError *blad = NULL;
	gchar *raw_kfile = g_key_file_to_data(m_key_file, NULL, &blad);
	
	FILE *plik_konfiguracji = fopen(m_file, "w+");
	if (!plik_konfiguracji) g_error("Nie mozna utworzyć domyśnego pliku konfigutracji w %s\n", m_file);
	fprintf(plik_konfiguracji, raw_kfile);

	/* Czystki: */
	fclose(plik_konfiguracji);
	g_free(raw_kfile);
	g_free(m_file);
	g_key_file_free(m_key_file);
}
