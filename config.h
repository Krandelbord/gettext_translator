#ifndef CONFIG_H
#define CONFIG_H

#define PROGRAM_NAME "Gettext Translator"
#define PROGRAM_VERSION "0.9"

#ifdef DEBUG
#include <glib.h>
#include <stdio_ext.h>
#  define debug(args...) { \
	GTimeVal time; \
	g_get_current_time(&time); \
	char buf[BUFSIZ]; \
	strftime(buf, sizeof(buf), "%H:%M:%S", gmtime(&(time.tv_sec))); \
	g_print("\033[6;102m%s,%2.0f ", buf, time.tv_usec/1000.0); \
	g_print("%s\033[1;0m\t", __PRETTY_FUNCTION__); \
	g_print (args); \
}
#else
#  define debug(args...) ;
#endif /* end of DEBUG MACRO */

#include <libintl.h>
#define PACKAGE PROGRAM_NAME
#define _(s) gettext(s)

#endif /* CONFIG_H */
