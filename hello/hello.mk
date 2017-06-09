# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

# Also note that most variable names are prepended with the package name to
# ensure uniqueness. This prevents conflicts when multiple Makefiles are called
# recursively.

HELLO_SRC_DIR = hello/src
HELLO_TEST_DIR = hello/test
HELLO_INSTALL_DIR = usr/bin# Relative to root directory in target file system.

ifndef target
    HELLO_EXE = hello/hello
else
    HELLO_EXE = $(OVERLAY_DIR)/$(INSTALL_DIR)/hello
endif

HELLO_TEST_EXE = hello/hello-test
HELLO_BUILD_DIR = hello/$(BUILD_DIR)

HELLO_SRC_FILES := $(wildcard $(HELLO_SRC_DIR)/*.c)
# Exclude <pkg_name>.c from source files to prevent multiple main functions from
# being compiled when building unit tests.
#HELLO_SRC_FILES := $(filter-out $(HELLO_SRC_DIR)/hello.c, $(HELLO_SRC_FILES))
HELLO_SRC_OBJS := $(patsubst $(HELLO_SRC_DIR)/%.c, $(HELLO_BUILD_DIR)/%.o, $(HELLO_SRC_FILES))

HELLO_TEST_FILES := $(wildcard $(HELLO_TEST_DIR)/*.cpp)
HELLO_TEST_OBJS := $(patsubst $(HELLO_TEST_DIR)/%.cpp, $(HELLO_BUILD_DIR)/%.o, $(HELLO_TEST_FILES))
HELLO_DEPS := $(HELLO_OBJS:.o=.d)

# Include generated makefiles containing object dependencies unless the clean
# target was specified.
ifeq ($(filter $(MAKECMDGOALS), build clean),)
    -include $(HELLO_DEPS)
endif

.PHONY += hello hello_test hello_clean

hello: $(HELLO_EXE)
hello_test: $(HELLO_TEST_EXE)

# Removes the build directory containing object files, but not the executables
# in the external tree. If the target is the local machine, then the executable
# will appear in the project directory, in which case it is deleted as well.
hello_clean:
	@rm -rf $(HELLO_BUILD_DIR)
ifndef target
	@rm -f $(HELLO_EXE) $(HELLO_TEST_EXE)
endif

$(HELLO_EXE): $(HELLO_SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

$(HELLO_TEST_EXE): $(HELLO_TEST_OBJS) $(filter-out $(HELLO_BUILD_DIR)/hello.o, $(HELLO_SRC_OBJS)) $(GTEST_BUILD_DIR)/gtest_main.a
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LD_FLAGS)

$(HELLO_BUILD_DIR)/%.o: $(HELLO_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(HELLO_BUILD_DIR)/%.o: $(HELLO_TEST_DIR)/%.cpp $(GTEST_HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -I$(HELLO_SRC_DIR) -c -o $@ $<

# Automatically detect dependencies.
$(HELLO_BUILD_DIR)/%.d: $(HELLO_SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(HELLO_BUILD_DIR)/%.d: $(HELLO_TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(TEST_FLAGS) -MM -MT $(@:.d=.o) $< > $@
