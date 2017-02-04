EXE = hello
BUILD_DIR = build
SRC_DIR = src

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
DEBUG_CFLAGS = -g
RELEASE_CFLAGS = -O2 -s -DNDEBUG

.PHONY = all clean

ifeq ($(mode), debug)
	CFLAGS += DEBUG_CFLAGS
else ifeq ($(mode), 

clean:
	@echo cleaning!
