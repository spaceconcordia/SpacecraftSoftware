# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

# Also note that most variable names are prepended with the package name to
# ensure uniqueness. This prevents conflicts when multiple Makefiles are called
# recursively.

SCHEDULER_SRC_DIR = scheduler/src
SCHEDULER_TEST_DIR = scheduler/test
SCHEDULER_INSTALL_DIR = usr/bin# Relative to root directory in target file system.

ifndef target
    SCHEDULER_EXE = scheduler/scheduler
else
    SCHEDULER_EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/scheduler
endif

SCHEDULER_TEST_EXE = scheduler/scheduler-test
SCHEDULER_BUILD_DIR = scheduler/$(BUILD_DIR)

SCHEDULER_SRC_FILES := $(wildcard $(SCHEDULER_SRC_DIR)/*.c)
# Exclude <pkg_name>.c from source files to prevent multiple main functions from
# being compiled when building unit tests.
SCHEDULER_SRC_FILES := $(filter-out $(SCHEDULER_SRC_DIR)/scheduler.c, $(SCHEDULER_SRC_FILES))
SCHEDULER_SRC_OBJS := $(patsubst $(SCHEDULER_SRC_DIR)/%.c, $(SCHEDULER_BUILD_DIR)/%.o, $(SCHEDULER_SRC_FILES))

SCHEDULER_TEST_FILES := $(wildcard $(SCHEDULER_TEST_DIR)/*.cpp)
SCHEDULER_TEST_OBJS := $(patsubst $(SCHEDULER_TEST_DIR)/%.cpp, $(SCHEDULER_BUILD_DIR)/%.o, $(SCHEDULER_TEST_FILES))
SCHEDULER_DEPS := $(SCHEDULER_OBJS:.o=.d)

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifeq ($(filter $(MAKECMDGOALS), build clean),)
    -include $(SCHEDULER_DEPS)
endif

.PHONY += scheduler scheduler_test scheduler_clean

scheduler: $(SCHEDULER_EXE)
scheduler_test: $(SCHEDULER_TEST_EXE)

# Removes the build directory containing object files, but not the executables
# in the external tree. If the target is the local machine, then the executable
# will appear in the project directory, in which case it is deleted as well.
scheduler_clean:
	@rm -rf $(SCHEDULER_BUILD_DIR)
ifndef target
	@rm -f $(SCHEDULER_EXE) $(SCHEDULER_TEST_EXE)
endif

$(SCHEDULER_EXE): $(SCHEDULER_SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(SCHEDULER_SRC_DIR)/scheduler.c $^

$(SCHEDULER_TEST_EXE): $(SCHEDULER_TEST_OBJS) $(SCHEDULER_SRC_OBJS) $(GTEST_BUILD_DIR)/gtest_main.a
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LD_FLAGS)

$(SCHEDULER_BUILD_DIR)/%.o: $(SCHEDULER_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(SCHEDULER_BUILD_DIR)/%.o: $(SCHEDULER_TEST_DIR)/%.cpp $(GTEST_HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -I$(SCHEDULER_SRC_DIR) -c -o $@ $<

# Automatically detect dependencies.
$(SCHEDULER_BUILD_DIR)/%.d: $(SCHEDULER_SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(SCHEDULER_BUILD_DIR)/%.d: $(SCHEDULER_TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@
