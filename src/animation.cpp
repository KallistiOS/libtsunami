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

void Animation::triggerAdd(std::shared_ptr<Trigger> t) {
	m_triggers.push_front(t);
}

void Animation::triggerRemove(Trigger *tr) {
	auto is_ptr = [=](std::shared_ptr<Trigger> sp) { return sp.get() == tr; };
	auto it = std::find_if(m_triggers.begin(), m_triggers.end(), is_ptr);

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
