#ifndef CONFIG_H
#define CONFIG_H

#define PROGRAM_NAME "Gettext Translator"
#define PROGRAM_VERSION "0.8 beta"

#ifdef DEBUG
#include <glib.h>
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

/* MODIFERIS definitions */
#define 	MOD__SHIFT   (event->state & GDK_SHIFT_MASK)	
#define 	MOD__CTRL   (event->state & GDK_CONTROL_MASK)
#define 	MOD__ALT   (event->state & GDK_MOD1_MASK)
#define 	MOD__SHIFT_ONLY   ((event->state & GDK_SHIFT_MASK) && !(event->state & GDK_CONTROL_MASK) && !(event->state & GDK_MOD1_MASK))
#define 	MOD__CTRL_ONLY   (!(event->state & GDK_SHIFT_MASK) && (event->state & GDK_CONTROL_MASK) && !(event->state & GDK_MOD1_MASK))
#define 	MOD__ALT_ONLY   (!(event->state & GDK_SHIFT_MASK) && !(event->state & GDK_CONTROL_MASK) && (event->state & GDK_MOD1_MASK))

#endif /* CONFIG_H */
