# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually.

# PKG_NAME: name of the package.
# PKG_INSTALL_DIR: where in the root directory to install. 
# PKG_FLAGS: package-specific flags to pass to the compiler. possibly empty.
# PKG_LD_FLAGS: package-specific flags to pass to the linker. possibly empty.
PKG_NAME = logger
PKG_INSTALL_DIR = usr/bin
PKG_LD_FLAGS = -lsqlite3

include ../common/common.mk
