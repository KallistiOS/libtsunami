/*
   Tsunami for KallistiOS ##version##

   death.cpp

   Copyright (C) 2002 Megan Potter
*/

#include "triggers/death.h"
#include "drawable.h"

Death::Death(std::shared_ptr<Drawable> target) {
	m_target = target;
}

Death::~Death() {
}

void Death::trigger(Drawable *t, Animation *a) {
	// Mark our parent drawable as "finished"
	if (m_target)
		m_target->setFinished();
	else
		t->setFinished();

	// Go the way of the dodo ourselves
	Trigger::trigger(t, a);
}
