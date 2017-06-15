# This makefile defines variables and rules that are used by multiple packages.

# The following variables are expected to be defined by the root makefile:
#   BUILD_DIR
#   OVERLAY_DIR
#   CFLAGS
#   LD_FLAGS
#   TEST_FLAGS
#   TEST_LD_FLAGS
#   CC
#   CXX
#
# The following variables are expected to be defined by the calling makefile:
#   PKG_NAME
#   PKG_INSTALL_DIR
#   PKG_FLAGS (possibly empty)
#   PKG_LD_FLAGS (possibly empty)

SRC_DIR = src
# If target is not defined, place executable in package directory. Else place
# in overlay directory.
LOCAL_EXE_PATH = $(PKG_NAME)
OVERLAY_EXE_PATH = $(OVERLAY_DIR)/$(PKG_INSTALL_DIR)/$(PKG_NAME)
ifndef target
    EXE = $(LOCAL_EXE_PATH)
else
    EXE = $(OVERLAY_EXE_PATH)
endif
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TEST_DIR = test
TEST_EXE = $(PKG_NAME)-test
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_FILES))

# Include generated makefiles containing object dependencies unless the
# <package_name>-clean target was called.
DEPS := $(SRC_OBJS:.o=.d)
ifneq ($(MAKECMDGOALS), $(PKG_NAME)-clean)
    -include $(DEPS)
endif

.PHONY = $(PKG_NAME) $(PKG_NAME)-test $(PKG_NAME)-clean

# Set the <package_name> and <package_name> targets to the executable and test
# executable respectively *unless* they have the same name, in which case there
# is no point and make will complain about circular dependencies.
ifneq ($(PKG_NAME), $(EXE))
    $(PKG_NAME): $(EXE)
endif
ifneq ($(PKG_NAME), $(TEST_EXE))
    $(PKG_NAME)-test: $(TEST_EXE)
endif

# Removes the build directory containing object files and the executables.
$(PKG_NAME)-clean:
	rm -rf $(BUILD_DIR_ROOT)
	rm -f $(EXE) $(TEST_EXE)

$(EXE): $(SRC_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(PKG_FLAGS) -o $@ $^ $(PKG_LD_FLAGS)

$(TEST_EXE): $(TEST_OBJS) $(filter-out $(BUILD_DIR)/$(PKG_NAME).o, $(SRC_OBJS))
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -o $@ $^ $(TEST_LD_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(TEST_FLAGS) -I$(SRC_DIR) -c -o $@ $<

# Automatically detect dependencies.
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

$(BUILD_DIR)/%.d: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(TEST_FLAGS) -MM -MT $(@:.d=.o) $< > $@
