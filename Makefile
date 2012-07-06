# Tsunami for KallistiOS ##version##
#
# Makefile
# (c)2002 Dan Potter

TARGET := libtsunami.a

# Main sources
OBJS_MAIN := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

# Drawables
OBJS_DRW := $(patsubst %.cpp,%.o,$(wildcard src/drawables/*.cpp))

# Animations
OBJS_ANIMS := $(patsubst %.cpp,%.o,$(wildcard src/anims/*.cpp))

# Triggers
OBJS_TRIGS := $(patsubst %.cpp,%.o,$(wildcard src/triggers/*.cpp))

OBJS := $(OBJS_MAIN) $(OBJS_DRW) $(OBJS_ANIMS) $(OBJS_TRIGS)

defaultall: create_kos_link $(OBJS) subdirs linklib
 
# creates the kos link to the headers
create_kos_link:
	rm -f ../include/tsu
	ln -s ../libtsunami/include ../include/tsu

# Grab the shared Makefile pieces
include $(KOS_BASE)/addons/Makefile.prefab
