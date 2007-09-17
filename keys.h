#ifndef KEYS_H
#define KEYS_H

/* MODIFERIS definitions */
#define 	MOD__SHIFT   (event->state & GDK_SHIFT_MASK)	
#define 	MOD__CTRL   (event->state & GDK_CONTROL_MASK)
#define 	MOD__ALT   (event->state & GDK_MOD1_MASK)
#define 	MOD__SHIFT_ONLY   ((event->state & GDK_SHIFT_MASK) && !(event->state & GDK_CONTROL_MASK) && !(event->state & GDK_MOD1_MASK))
#define 	MOD__CTRL_ONLY   (!(event->state & GDK_SHIFT_MASK) && (event->state & GDK_CONTROL_MASK) && !(event->state & GDK_MOD1_MASK))
#define 	MOD__ALT_ONLY   (!(event->state & GDK_SHIFT_MASK) && !(event->state & GDK_CONTROL_MASK) && (event->state & GDK_MOD1_MASK))
/* END OF MODIFERIS definitions */

#define		KEY__CTRL_SPACE event->keyval==32 && MOD__CTRL_ONLY
#define 	KEY_COPY_MSGID KEY__CTRL_SPACE

#endif /* KEYS_H */
