# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

# Also note that most variable names are prepended with the package name to
# ensure uniqueness. This prevents conflicts when multiple Makefiles are called
# recursively.

LOGGER_SRC_DIR = logger/src
LOGGER_TEST_DIR = logger/test
LOGGER_INSTALL_DIR = usr/bin# Relative to root directory in target file system.

ifndef target
    LOGGER_EXE = logger/logger
else
    LOGGER_EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/logger
endif

LOGGER_TEST_EXE = logger/logger-test
LOGGER_BUILD_DIR = logger/$(BUILD_DIR)

LOGGER_SRC_FILES := $(wildcard $(LOGGER_SRC_DIR)/*.c)
LOGGER_SRC_OBJS := $(patsubst $(LOGGER_SRC_DIR)/%.c, $(LOGGER_BUILD_DIR)/%.o, $(LOGGER_SRC_FILES))

LOGGER_TEST_FILES := $(wildcard $(LOGGER_TEST_DIR)/*.cpp)
LOGGER_TEST_OBJS := $(patsubst $(LOGGER_TEST_DIR)/%.cpp, $(LOGGER_BUILD_DIR)/%.o, $(LOGGER_TEST_FILES))
LOGGER_DEPS := $(LOGGER_OBJS:.o=.d)

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifeq ($(filter $(MAKECMDGOALS), build clean),)
    -include $(LOGGER_DEPS)
endif

.PHONY += logger logger_test logger_clean

logger: $(LOGGER_EXE)
logger_test: $(LOGGER_TEST_EXE)

# Removes the build directory containing object files, but not the executables
# in the external tree. If the target is the local machine, then the executable
# will appear in the project directory, in which case it is deleted as well.
logger_clean:
	@rm -rf $(LOGGER_BUILD_DIR)
ifndef target
	@rm -f $(LOGGER_EXE) $(LOGGER_TEST_EXE)
endif

$(LOGGER_EXE): $(LOGGER_SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(LOGGER_SRC_DIR)/logger.c $^ -lsqlite3

$(LOGGER_TEST_EXE): $(LOGGER_TEST_OBJS) $(filter-out $(LOGGER_BUILD_DIR)/logger.o, $(LOGGER_SRC_OBJS)) $(GTEST_BUILD_DIR)/gtest_main.a
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LD_FLAGS)

$(LOGGER_BUILD_DIR)/%.o: $(LOGGER_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(LOGGER_BUILD_DIR)/%.o: $(LOGGER_TEST_DIR)/%.cpp $(GTEST_HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -I$(LOGGER_SRC_DIR) -c -o $@ $<

# Automatically detect dependencies.
$(LOGGER_BUILD_DIR)/%.d: $(LOGGER_SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(LOGGER_BUILD_DIR)/%.d: $(LOGGER_TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(TEST_FLAGS) -MM -MT $(@:.d=.o) $< > $@
