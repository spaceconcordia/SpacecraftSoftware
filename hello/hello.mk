EXE_NAME = hello
BUILD_DIR = build
INSTALL_DIR = usr/bin# Relative to root directory in target file system.
SRC_DIR = src

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
RELEASE_CFLAGS = -O2 -s -DNDEBUG
DEBUG_CFLAGS = -g

.PHONY = all clean check_target check_mode

# Check if the target variable was set on the command line. If not, set
# NO_TARGET to 1. If target was set to an invalid value, throw an error.
NO_TARGET = 1
ifeq ($(target), qemu)
    OVERLAY_DIR = ../ext-tree/board/qemu/overlay
    EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/$(EXE_NAME)
    NO_TARGET = 0
else
ifeq ($(target), arietta)
    $(error target arietta is not currently supported)
else
ifdef target
    $(error target must be set to qemu or arietta)
endif
endif
endif

# Check if the mode variable was set on the command line. If not, set NO_MODE to
# 1. If mode was set to an invalid value, throw an error.
NO_MODE = 1
ifeq ($(mode), release)
    CFLAGS += $(RELEASE_CFLAGS)
    BUILD_DIR := $(BUILD_DIR)/release
    NO_MODE = 0
else
ifeq ($(mode), debug)
    CFLAGS += $(DEBUG_CFLAGS)
    BUILD_DIR := $(BUILD_DIR)/debug
    NO_MODE = 0
else
ifdef mode
    $(error mode must be set to release or debug)
endif
endif
endif

C_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))
DEPS := $(OBJS:.o=.d)

all: $(EXE) | check_target check_mode

# Removes the build directory containing object files, but not the executables
# in the external tree.
clean:
	@if [ -d $(BUILD_DIR) ]; then rm -r $(BUILD_DIR); fi

# Throw an error if target was not set.
check_target:
ifeq ($(NO_TARGET), 1)
	@>&2 echo "error: target was not set."
	@exit 1
endif

# Throw an error if mode was not set.
check_mode:
ifeq ($(NO_MODE), 1)
	@>&2 echo "error: mode was not set."
	@exit 1
endif

$(EXE): $(OBJS) | check_target check_mode
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | check_target check_mode
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

# Automatically detect dependencies.
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c | check_target check_mode
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifneq ($(MAKECMDGOALS), clean)
    -include $(DEPS)
endif
