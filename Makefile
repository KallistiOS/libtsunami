# Tsunami for KallistiOS ##version##
#
# Makefile
# Copyright (C) 2002 Megan Potter

TARGET     := libtsunami.a
KOS_CFLAGS += -Iinclude

# Main sources
OBJS_MAIN  := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

# Drawables
OBJS_DRW   := $(patsubst %.cpp,%.o,$(wildcard src/drawables/*.cpp))

# Animations
OBJS_ANIMS := $(patsubst %.cpp,%.o,$(wildcard src/anims/*.cpp))

# Triggers
OBJS_TRIGS := $(patsubst %.cpp,%.o,$(wildcard src/triggers/*.cpp))

OBJS       := $(OBJS_MAIN) $(OBJS_DRW) $(OBJS_ANIMS) $(OBJS_TRIGS)

# Grab the shared Makefile pieces
include $(KOS_BASE)/addons/Makefile.prefab
