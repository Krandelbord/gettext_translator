#ifndef CONFIG_H
#define CONFIG_H

#ifdef DEBUG
#include <glib.h>
#  define debug(args...) g_print (args)
#else
#  define debug(args...) ;
#endif

#endif /* CONFIG_H */
