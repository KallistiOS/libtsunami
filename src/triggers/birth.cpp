/*
   Tsunami for KallistiOS ##version##

   birth.cpp

   Copyright (C) 2003 Megan Potter
*/

#include "triggers/birth.h"
#include "drawable.h"

Birth::Birth(std::shared_ptr<Drawable> newDrawable,
	     std::shared_ptr<Drawable> target) {
	m_newDrawable = newDrawable;
	m_target = target;
}

Birth::~Birth() {
}

void Birth::trigger(Drawable *t, Animation *a) {
	// Insert the next object into the parent
	if (m_target)
		m_target->subAdd(m_newDrawable);
	else
		t->subAdd(m_newDrawable);

	// Remove ourselves
	Trigger::trigger(t, a);
}
