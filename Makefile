#!/usr/bin/make
#
# sonic-infinite-scroller-game-dev				May 21, 2025
#
# source: Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2025 Misael Diaz-Maldonado
#
# This file is released under the GNU General Public License version 2 only
# as published by the Free Software Foundation.
#

include make-inc

export CC
export CCOPT
export LIBS

all: game

game:
	@mkdir -p obj && mkdir -p bin
	@$(MAKE) -C src
clean:
	@$(MAKE) -C src clean
