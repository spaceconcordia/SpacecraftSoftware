# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

PKG_NAME = hello
PKG_TYPE = exec
INSTALL_DIR = usr/bin# Relative to root directory in target file system.

SRC_DIR = $(PKG_NAME)/src
TEST_DIR = $(PKG_NAME)/test

# Set executable or library output path based on 1) the compile target, and 2)
# the package type. Unit tests are exclusively built in the project directory.
# Package build directory is set based on BUILD_DIR.
ifeq ($(PKG_TYPE), exec)
ifndef target
    EXE = $(PKG_NAME)/$(PKG_NAME)
else
    EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/$(PKG_NAME)
endif
else
ifeq ($(PKG_TYPE), s_lib)
    SLIB = $(PKG_NAME)/lib$(PKG_NAME).a
endif
endif
TEST_EXE = $(PKG_NAME)/$(PKG_NAME)-test
PKG_BUILD_DIR = $(PKG_NAME)/$(BUILD_DIR)

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
ifeq ($(PKG_TYPE), exec)
    SRC_FILES := $(filter-out $(SRC_DIR)/$(PKG_NAME).c, $(SRC_FILES))
endif
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(PKG_BUILD_DIR)/%.o, $(SRC_FILES))
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(PKG_BUILD_DIR)/%.o, $(TEST_FILES))
DEPS := $(OBJS:.o=.d)

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifeq ($(filter $(MAKECMDGOALS), build clean),)
    -include $(DEPS)
endif

.PHONY += $(PKG_NAME) $(PKG_NAME)_test $(PKG_NAME)_clean

# Set the main goal based on the package type.
ifeq ($(PKG_TYPE), exec)
    $(PKG_NAME): $(EXE)
else
ifeq ($(PKG_TYPE), s_lib)
    $(PKG_NAME): $(SLIB)
endif
endif

$(PKG_NAME)_test: $(TEST_EXE)

# Removes the build directory containing object files, but not the executables
# in the external tree. If the target is the local machine, then the executable
# will appear in the project directory, in which case it is deleted as well.
$(PKG_NAME)_clean:
	@if [ -d $(PKG_BUILD_DIR) ]; then rm -r $(PKG_BUILD_DIR); fi
ifndef target
	@rm -f $(EXE) $(SLIB) $(TEST_EXE)
endif

$(EXE): $(SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/$(PKG_NAME).c $^ 

$(SLIB): $(SRC_OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

$(TEST_EXE): $(TEST_OBJS) $(SRC_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LD_FLAGS)

$(PKG_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PKG_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -I$(SRC_DIR) -c -o $@ $<

# Automatically detect dependencies.
$(PKG_BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(PKG_BUILD_DIR)/%.d: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(TEST_FLAGS) -MM -MT $(@:.d=.o) $< > $@
