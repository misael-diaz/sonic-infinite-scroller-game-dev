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

$(SYSTEM_OBJ): \
	$(GMDEFS_H) \
	$(SYSTEM_H) \
	$(SYSTEM_SRC)
	$(CC) $(CCOPT) -c $(SYSTEM_SRC) -o $(SYSTEM_OBJ)
$(GRAPHIC_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(GRAPHIC_H) \
	$(GRAPHIC_SRC)
	$(CC) $(CCOPT) -c $(GRAPHIC_SRC) -o $(GRAPHIC_OBJ)
$(VIDEO_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(VIDEO_H) \
	$(VIDEO_SRC)
	$(CC) $(CCOPT) -c $(VIDEO_SRC) -o $(VIDEO_OBJ)
$(INPUT_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(INPUT_H) \
	$(INPUT_SRC)
	$(CC) $(CCOPT) -c $(INPUT_SRC) -o $(INPUT_OBJ)
$(ENTITY_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(GRAPHIC_H) \
	$(VIDEO_H) \
	$(ENTITY_H) \
	$(ENTITY_SRC)
	$(CC) $(CCOPT) -c $(ENTITY_SRC) -o $(ENTITY_OBJ)
$(GAME_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(SYSTEM_H) \
	$(VIDEO_H) \
	$(INPUT_H) \
	$(GAME_H) \
	$(GAME_SRC)
	$(CC) $(CCOPT) -c $(GAME_SRC) -o $(GAME_OBJ)
$(MAIN_OBJ): \
	$(DEFS_H) \
	$(TYPES_H) \
	$(GRAPHIC_H) \
	$(SYSTEM_H) \
	$(VIDEO_H) \
	$(INPUT_H) \
	$(ENTITY_H) \
	$(GAME_H) \
	$(MAIN_SRC)
	$(CC) $(CCOPT) -c $(MAIN_SRC) -o $(MAIN_OBJ)
$(BIN): \
	$(GRAPHIC_OBJ) \
	$(SYSTEM_OBJ) \
	$(VIDEO_OBJ) \
	$(INPUT_OBJ) \
	$(ENTITY_OBJ) \
	$(GAME_OBJ) \
	$(MAIN_OBJ)
	$(CC) $(CCOPT) \
		$(GRAPHIC_OBJ) \
		$(SYSTEM_OBJ) \
		$(VIDEO_OBJ) \
		$(INPUT_OBJ) \
		$(ENTITY_OBJ) \
		$(GAME_OBJ) \
		$(MAIN_OBJ) \
		-o \
		$(BIN) \
		$(LIBS)
clean:
	rm -f ../obj/*.o
	rm -f $(BIN)
