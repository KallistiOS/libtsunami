/* 
   Tsunami for KallistiOS ##version##
   
   trigger.cpp
   
   (c)2002 Dan Potter
*/

#include <tsu/trigger.h>
#include <tsu/animation.h>

Trigger::Trigger() {
}

Trigger::~Trigger() {
}

void Trigger::trigger(Drawable *t, Animation *a) {
	// Autoclean ourselves once we've triggered
	a->triggerRemove(this);
}

