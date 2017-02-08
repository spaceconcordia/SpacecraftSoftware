# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

PKG_NAME = hello
INSTALL_DIR = usr/bin# Relative to root directory in target file system.
SRC_DIR = $(PKG_NAME)/src
TEST_DIR = $(PKG_NAME)/test

# Set executable paths based on OVERLAY_DIR and package build directory based on
# BUILD_DIR.
EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/$(PKG_NAME)
TEST_EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/$(PKG_NAME)-test
PKG_BUILD_DIR = $(PKG_NAME)/$(BUILD_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(PKG_BUILD_DIR)/%.o, $(SRC_FILES))
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(PKG_BUILD_DIR)/%.o, $(TEST_FILES))
DEPS := $(OBJS:.o=.d)

# Linker commands for check unit test framework.
TEST_LD = -lcheck -lsubunit -lrt -lm -pthread

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifeq ($(filter $(MAKECMDGOALS), build clean),)
    -include $(DEPS)
endif

.PHONY += $(PKG_NAME) $(PKG_NAME)_test $(PKG_NAME)_clean

$(PKG_NAME): $(EXE)

$(PKG_NAME)_test: $(TEST_EXE)

# Removes the build directory containing object files, but not the executables
# in the external tree.
$(PKG_NAME)_clean:
	@if [ -d $(PKG_BUILD_DIR) ]; then rm -r $(PKG_BUILD_DIR); fi

$(EXE): $(SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(TEST_EXE): $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $< $(TEST_LD)

$(PKG_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PKG_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

# Automatically detect dependencies.
$(PKG_BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(PKG_BUILD_DIR)/%.d: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@
