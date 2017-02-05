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
    BUILD_DIR += /release
else
ifeq ($(mode), debug)
    CFLAGS += DEBUG_CFLAGS
    BUILD_DIR += /debug
else
    $(error mode was not set or set to an invalid value.)
endif
endif

C_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))
DEPS := $(OBJS:.o=.d)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(EXE) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Automatically detect dependencies.
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -MM -MT $(@:.d=.o) $< > $@
-include $(DEPS)
