/*
   Tsunami for KallistiOS ##version##

   animation.cpp

   Copyright (C) 2002 Megan Potter
*/

#include "animation.h"
#include "drawable.h"

#include <algorithm>

Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::triggerAdd(Trigger *t) {
	m_triggers.push_front(t);
}

void Animation::triggerRemove(Trigger *tr) {
	auto it = std::find(m_triggers.begin(), m_triggers.end(), tr);

	if (it != m_triggers.end())
		m_triggers.erase(it);
}

void Animation::triggerRemoveAll() {
	m_triggers.clear();
}

void Animation::nextFrame(Drawable *t) {
}

void Animation::trigger(Drawable *d) {
	/* Duplicate the array of triggers. This makes the "for" loop much
	 * easier as we don't have to handle it->trigger() calling
	 * triggerRemove(). */
	auto triggers = m_triggers;

	for (auto it: m_triggers) {
		it->trigger(d, this);
	}
}

void Animation::complete(Drawable *d) {
	// Call any completion triggers
	trigger(d);

	// Remove us from the parent Drawable
	d->animRemove(this);
}
