/*
 * module_mouse_clark2.h
 *
 */

#ifndef MODULE_MOUSE_CLARK2_H_
#define MODULE_MOUSE_CLARK2_H_

void init_mouse_clark2 (void); // [miml:init]
void finalize_mouse_clark2 (void); // [miml:final]
extern void sendMessage_mouse_clark2(const char *src, unsigned char *buffer, int length); // [miml:sender]

#endif /* MODULE_MOUSE_CLARK2_H_ */
