# Each package must have a makefile with the name <package_name>.mk which
# defines the following goals:
# <package_name>: builds the package.
# <package_name>-test: builds the unit tests for the package.
# <package_name>-clean: removes object files and executables generated by
#                       package.
PACKAGES = hello

# These variables are used by packages when they build their targets. Note that
# these variables may be modified based on the variables `target` and `mode`
# that are set on the command line.
#
# BUILD_DIR_ROOT: root directory where all object files are placed. relative to
#                 *package* directory.
# BUILD_DIR: directory to place object files for specific target and mode.
#            relative to *package* directory.
# BUILDROOT_DIR: directory containing buildroot files.
# BUILDROOT_OUTPUT_DIR: directory where buildroot files will be build.
# OVERLAY_DIR: directory containing the root filesystem overlay.
# CFLAGS: flags to use with C compiler.
# RELEASE_CFLAGS: additional flags to use with C compiler in release mode.
# DEBUG_CFLAGS: additional flags to use with C compiler in debug mode.
# COVERAGE_FLAGS: flags to create test coverage files.
# LD_FLAGS: flags to use by the linker.
# TEST_FLAGS: flags to use when building unit tests.
# TEST_LD_FLAGS: flags to use by linker for unit tests.
export BUILD_DIR_ROOT = build
export BUILD_DIR = $(BUILD_DIR_ROOT)
BUILDROOT_DIR = $(shell echo ~)/buildroot-2017.05
BUILDROOT_OUTPUT_DIR = $(BUILDROOT_DIR)/output
EXT_TREE = $(shell pwd)/ext-tree
export OVERLAY_DIR = $(EXT_TREE)/board
export CFLAGS = -std=c99 -Wall -Wextra -pedantic -Werror
RELEASE_CFLAGS = -O2 -s -DNDEBUG
DEBUG_CFLAGS = -g
COVERAGE_CFLAGS = -fprofile-arcs -ftest-coverage
export LD_FLAGS =
export TEST_FLAGS = -std=c++11 -g
export TEST_LD_FLAGS = -lgtest -lgtest_main -pthread -lgcov --coverage

# Check if the `target` variable was set on the command line. If not, local
# machine becomes the target by default. If target is invalid, throw an error
# no matter what. Presently the supported values for target are `arietta-128`
# and `arietta-wifi-128`.
#
# The following variables are modified or created based on the target:
# BUILD_DIR: modified based on target.
# CC: path to C compiler.
# CXX: path to C++ compiler.
# BUILD_DIR: modified based on target.
# BUILDROOT_DIR: modified based on target.
# OVERLAY_DIR: modified based on target.
ifndef target
    export CC = gcc
    export CXX = g++
else
ifeq ($(target), $(filter $(target), arietta-128 arietta-wifi-128))
    BUILD_DIR := $(BUILD_DIR)/$(target)
    BUILDROOT_OUTPUT_DIR := $(BUILDROOT_OUTPUT_DIR)/$(target)
    export CC = arm-linux-cc
    OVERLAY_DIR := $(OVERLAY_DIR)/$(target)/overlay

    # Prepend directory containing compiler to PATH.
    export PATH := $(BUILDROOT_OUTPUT_DIR)/host/usr/bin:$(PATH)
else
    $(error target must be arietta-128 or arietta-wifi-128)
endif
endif

# Check if the mode variable was set on the command line. If not, throw an error
# unless a goal that does not require a mode was called. If mode is invalid,
# throw an error no matter what.
#
# The following variables are modified based on the release mode:
# BUILD_DIR
# CFLAGS
ifeq ($(mode), release)
    BUILD_DIR := $(BUILD_DIR)/release
    CFLAGS += $(RELEASE_CFLAGS)
else
ifeq ($(mode), debug)
    BUILD_DIR := $(BUILD_DIR)/debug
    CFLAGS += $(DEBUG_CFLAGS)
else
ifdef mode
    $(error mode must be set to release or debug)
else
ifeq ($(filter $(MAKECMDGOALS), build clean menuconfig nuke),)
    $(error mode must be specified)
endif
endif
endif
endif

# TODO
# Only include coverage flags only when debug and not tests
ifeq ($(mode), debug)
ifeq ($(filter $(MAKECMDGOALS), test),)
	CFLAGS += $(COVERAGE_CFLAGS)
endif
endif

.PHONY = all build clean defconfig dl-buildroot menuconfig nuke test toolchain

# Build all the packages. If target is specified, the cross-compilation
# toolchain will be built first.
all: toolchain
	@for pkg in $(PACKAGES); do \
		$(MAKE) -C $$pkg -f $$pkg.mk $$pkg; \
	done

# Only include test goal if building locally. Unit tests on other targets are
# not presently supported.
ifndef target
    test:
	@for pkg in $(PACKAGES); do \
		$(MAKE) -C $$pkg -f $$pkg.mk $$pkg-test; \
	done
	@for pkg in $(PACKAGES); do \
		./$$pkg/$$pkg-test; \
	done
endif

# Build the embedded Linux OS with external tree.
build: defconfig
ifndef target
	$(error target must be specified)
else
	$(MAKE) -C $(BUILDROOT_DIR) O=$(BUILDROOT_OUTPUT_DIR)
endif

# Call the clean goal in each package makefile.
clean:
	@for pkg in $(PACKAGES); do \
		$(MAKE) -C $$pkg -f $$pkg.mk $$pkg-clean; \
	done

# Apply defconfig.
defconfig: dl-buildroot
	@mkdir -p $(BUILDROOT_OUTPUT_DIR)
	$(MAKE) -C $(BUILDROOT_DIR) O=$(BUILDROOT_OUTPUT_DIR) \
		BR2_EXTERNAL=$(EXT_TREE) sc_$(target)_defconfig

# Download buildroot in the home directory.
dl-buildroot:
	@if [ ! -d $(BUILDROOT_DIR) ]; then \
		cd ~; \
		wget https://buildroot.org/downloads/buildroot-2017.05.tar.bz2; \
		tar xjf buildroot-2017.05.tar.bz2; \
		rm buildroot-2017.05.tar.bz2; \
		cd; \
	fi

# Brings up an curses display for configuring the Linux system.
menuconfig: defconfig
ifndef target
	$(error target must be specified)
else
	$(MAKE) -C $(BUILDROOT_OUTPUT_DIR) MENUCONFIG_COLOR=blackbg menuconfig
	$(MAKE) -C $(BUILDROOT_OUTPUT_DIR) savedefconfig
endif

# Cleans the packages as well as the buildroot.
nuke: clean
	$(MAKE) -C $(BUILDROOT_OUTPUT_DIR) distclean

# Installs and compiles the buildroot toolchain. If target is specified and
# the toolchain is not installed then local packages cannot be compiled because
# they won't have access to the required compiler.
toolchain: defconfig
ifdef target
	$(MAKE) -C $(BUILDROOT_OUTPUT_DIR) toolchain;
endif
