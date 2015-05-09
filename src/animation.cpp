/*
   Tsunami for KallistiOS ##version##

   animation.cpp

   (c)2002 Dan Potter
*/

#include "animation.h"
#include "drawable.h"

Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::triggerAdd(Trigger *t) {
	m_triggers.insertHead(t);
}

void Animation::triggerRemove(Trigger *tr) {
	m_triggers.del(tr);
}

void Animation::triggerRemoveAll() {
	m_triggers.delAll();
}

void Animation::nextFrame(Drawable *t) {
}

void Animation::trigger(Drawable *d) {
	// Call each active trigger
	ListNode<Trigger> *t, *tn;

	t = m_triggers.getHead();
	while (t) {
		tn = t->getNext();
		(*t)->trigger(d, this);
		t = tn;
	}
}

void Animation::complete(Drawable *d) {
	// Call any completion triggers
	trigger(d);

	// Remove us from the parent Drawable
	d->animRemove(this);
}
