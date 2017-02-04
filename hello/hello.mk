EXE = hello
BUILD_DIR = build
SRC_DIR = src

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
RELEASE_CFLAGS = -O2 -s -DNDEBUG
DEBUG_CFLAGS = -g

.PHONY = all clean

ifeq ($(mode), release)
    CFLAGS += RELEASE_CFLAGS
else
ifeq ($(mode), debug)
    CFLAGS += DEBUG_CFLAGS
else
    $(error mode was not set or set to an invalid value.)
endif
endif

clean:
	@echo cleaning!
