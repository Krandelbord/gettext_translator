#ifndef CONFIG_H
#define CONFIG_H

#ifdef DEBUG
#include <glib.h>
#  define debug(args...) g_print("\033[6;102m%s\033[1;0m\t", __PRETTY_FUNCTION__); g_print (args)
#else
#  define debug(args...) ;
#endif

#endif /* CONFIG_H */
