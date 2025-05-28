#!/usr/bin/make
#
# gnu-linux-xlib-game-dev                           May 23, 2025
#
# source: src/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (C) 2025 Misael Diaz-Maldonado
#
# This file is released under the GNU General Public License version 2 only
# as published by the Free Software Foundation.
#

include make-inc

all: $(BIN)

# MISSING A LOT OF DEP RULES EVERYWHERE
# MAYBE ADD BUNDLES FOR DEFS AND TYPE HEADERS
$(GRAPHIC_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(GRAPHIC_H) \
	$(GRAPHIC_SRC)
	$(CC) $(CCOPT) -c $(GRAPHIC_SRC) -o $(GRAPHIC_OBJ)
$(ENTITY_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(GRAPHIC_H) \
	$(VIDEO_H) \
	$(ENTITY_H) \
	$(ENTITY_SRC)
	$(CC) $(CCOPT) -c $(ENTITY_SRC) -o $(ENTITY_OBJ)
$(SYSTEM_OBJ): \
	$(GMDEFS_H) \
	$(SYSTEM_H) \
	$(SYSTEM_SRC)
	$(CC) $(CCOPT) -c $(SYSTEM_SRC) -o $(SYSTEM_OBJ)
$(INPUT_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(INPUT_H) \
	$(INPUT_SRC)
	$(CC) $(CCOPT) -c $(INPUT_SRC) -o $(INPUT_OBJ)
$(VIDEO_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(VIDEO_H) \
	$(VIDEO_SRC)
	$(CC) $(CCOPT) -c $(VIDEO_SRC) -o $(VIDEO_OBJ)
$(GAME_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(SYSTEM_H) \
	$(INPUT_H) \
	$(VIDEO_H) \
	$(GAME_H) \
	$(GAME_SRC)
	$(CC) $(CCOPT) -c $(GAME_SRC) -o $(GAME_OBJ)
$(MAIN_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(SYSTEM_H) \
	$(INPUT_H) \
	$(VIDEO_H) \
	$(GRAPHIC_H) \
	$(ENTITY_H) \
	$(GAME_H) \
	$(SYSTEM_OBJ) \
	$(GRAPHIC_OBJ) \
	$(ENTITY_OBJ) \
	$(INPUT_OBJ) \
	$(VIDEO_OBJ) \
	$(GAME_OBJ) \
	$(MAIN_SRC)
	$(CC) $(CCOPT) -c $(MAIN_SRC) -o $(MAIN_OBJ)
$(BIN): $(MAIN_OBJ)
	$(CC) $(CCOPT) \
		$(ENTITY_OBJ) \
		$(SYSTEM_OBJ) \
		$(INPUT_OBJ) \
		$(VIDEO_OBJ) \
		$(GRAPHIC_OBJ) \
		$(GAME_OBJ) \
		$(MAIN_OBJ) \
		-o \
		$(BIN) \
		$(LIBS)
clean:
	rm -f ../obj/*.o
	rm -f $(BIN)
