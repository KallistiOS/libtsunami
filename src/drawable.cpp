/*
   Tsunami for KallistiOS ##version##

   drawable.cpp

   Copyright (C) 2002 Megan Potter
*/

#include "drawable.h"
#include <plx/matrix.h>

#include <algorithm>

// Constructor / Destructor
Drawable::Drawable() {
	m_trans.zero();
	m_rotate.zero();
	m_scale = Vector(1.0f, 1.0f, 1.0f, 1.0f);
	m_alpha = 1.0f;

	m_t_prelative = true;
	m_r_prelative = true;
	m_s_prelative = true;
	m_a_prelative = true;

	m_finished = false;
	m_subs_finished = false;

	m_parent = nullptr;
}

Drawable::~Drawable() {
}

void Drawable::animAdd(Animation * ani) {
	m_anims.push_front(ani);
}

void Drawable::animRemove(Animation *ani) {
	auto it = std::find(m_anims.begin(), m_anims.end(), ani);

	if (it != m_anims.end())
		m_anims.erase(it);
}

void Drawable::animRemoveAll() {
	m_anims.clear();
}

bool Drawable::isFinished() {
	if (!m_subs_finished) {
		for (auto it: m_subs) {
			if (!it->isFinished())
				return false;
		}

		m_subs_finished = true;
	}

	return m_finished;
}

void Drawable::setFinished() {
	m_finished = true;

	for (auto it: m_subs) {
		it->setFinished();
	}
}

void Drawable::subDraw(int list) {
	for (auto it: m_subs) {
		if (!it->isFinished())
			it->draw(list);
	}
}

void Drawable::subNextFrame() {
	for (auto it: m_subs) {
		if (!it->isFinished())
			it->nextFrame();
	}
}

void Drawable::subAdd(Drawable *t) {
	assert( t->m_parent == nullptr );
	t->m_parent = this;
	m_subs.push_front(t);
}

void Drawable::subRemove(Drawable *t) {
	t->m_parent = nullptr;

	auto it = std::find(m_subs.begin(), m_subs.end(), t);

	if (it != m_subs.end())
		m_subs.erase(it);
}

void Drawable::subRemoveFinished() {
	for (auto it = m_subs.begin(); it != m_subs.end();) {
		if ((*it)->isFinished()) {
			(*it)->m_parent = nullptr;
			it = m_subs.erase(it);
		} else {
			it++;
		}
	}
}

void Drawable::subRemoveAll() {
	for (auto it = m_subs.begin(); it != m_subs.end();) {
		(*it)->m_parent = nullptr;
		it = m_subs.erase(it);
	}
}

void Drawable::draw(int list) {
	subDraw(list);
}

void Drawable::nextFrame() {
	/* Duplicate the array of animations. This makes the "for" loop much
	 * easier as we don't have to handle it->nextFrame() calling
	 * animRemove(). */
	auto anims = m_anims;

	for (auto it: anims) {
		it->nextFrame(this);
	}

	subNextFrame();
}

Vector Drawable::getPosition() const {
	Vector pos = getTranslate();
	if (m_parent)
		pos += m_parent->getPosition();

	return pos;
}

Color Drawable::getColor() const {
	Color tint = getTint();
	if (m_parent)
		tint *= m_parent->getColor();

	return tint;
}

void Drawable::pushTransformMatrix() const {
	const Vector & pos = getTranslate();
	const Vector & rot = getRotate();
	const Vector & scale = getScale();

	plx_mat3d_push();
	plx_mat3d_translate(pos.x, pos.y, pos.z);
	plx_mat3d_rotate(rot.w, rot.x, rot.y, rot.z);
	plx_mat3d_scale(scale.x, scale.y, scale.z);
}

void Drawable::popTransformMatrix() const {
	plx_mat3d_pop();
}
