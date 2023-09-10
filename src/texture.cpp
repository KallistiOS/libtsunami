/*
   Tsunami for KallistiOS ##version##

   texture.cpp

   Copyright (C) 2002 Megan Potter
*/

#include "texture.h"

#include <kos/dbglog.h>

#include <cassert>

Texture::Texture(const std::filesystem::path &fn, bool use_alpha, bool yflip) {
	m_txr = nullptr;
	if (!loadFromFile(fn, use_alpha, yflip))
		assert( false );
}

Texture::Texture(int w, int h, int fmt) {
	m_txr = plx_txr_canvas(w, h, fmt);
	if (m_txr == nullptr) {
		dbglog(DBG_WARNING, "Texture::loadFromFile: Can't allocate %dx%dcanvas texture\n", w, h);
		assert( false );
	}
}

Texture::Texture() {
	m_txr = nullptr;
}

Texture::~Texture() {
	if (m_txr != nullptr)
		plx_txr_destroy(m_txr);
}

void Texture::setFilter(FilterType filter) {
	plx_txr_setfilter(m_txr, filter);
}

void Texture::setUVClamp(UVMode umode, UVMode vmode) {
	plx_txr_setuvclamp(m_txr, umode, vmode);
}

// Submit one of the poly headers
void Texture::sendHdr(int list) {
	plx_txr_send_hdr(m_txr, list, 0);
}

bool Texture::loadFromFile(const std::filesystem::path &fn, bool use_alpha, bool flip) {
	m_txr = plx_txr_load(fn.c_str(), use_alpha, flip ? PVR_TXRLOAD_INVERT_Y : 0);
	if (m_txr == nullptr) {
		dbglog(DBG_WARNING, "Texture::loadFromFile: Can't load '%s'\n", fn.c_str());
		return false;
	} else
		return true;
}
