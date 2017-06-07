# This makefile contains rules to build Google Test.

# GTEST_DIR: directory of googletest repository relative to project root.
# GTEST_BUILD_DIR: directory to build Google Test relative to project root.
# GTEST_CPPFLAGS: flags to pass to preprocessor.
# GTEST_CXXFLAGS: flags to pass to compiler.
# GTEST_HEADERS: Google Test header files.
# GTEST_SRCS: Google Test source files.
GTEST_DIR = googletest/googletest
GTEST_BUILD_DIR = googletest/build
GTEST_CPPFLAGS = -isystem $(GTEST_DIR)/include
GTEST_CXXFLAGS = -g -Wall -Wextra -pthread
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

.PHONY += gtest_clean

$(GTEST_BUILD_DIR)/gtest-all.o: $(GTEST_SRCS)
	@mkdir -p $(@D)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
		-o $@ $(GTEST_DIR)/src/gtest-all.cc

$(GTEST_BUILD_DIR)/gtest_main.o: $(GTEST_SRCS)
	@mkdir -p $(@D)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
		-o $@ $(GTEST_DIR)/src/gtest_main.cc

$(GTEST_BUILD_DIR)/gtest.a: gtest-all.o
	ar rcs $@ $^

$(GTEST_BUILD_DIR)/gtest_main.a: $(GTEST_BUILD_DIR)/gtest-all.o $(GTEST_BUILD_DIR)/gtest_main.o
	ar rcs $@ $^

gtest_clean:
	@rm -rf $(GTEST_BUILD_DIR)
