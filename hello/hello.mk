# Note that this makefile is expected to be called by the project's root
# Makefile. It should NOT be called manually. As a consequence, all directories
# are relative to the project root, not the package root.

# PKG_NAME: name of the package.
# PKG_TYPE: type of package. Can be either exec, s_lib (static library), or
#           d_lib (dynamic library).
# INSTALL_DIR: where in root directory to install. Not applicable for static
#              libraries.
PKG_NAME = hello
PKG_TYPE = exec
INSTALL_DIR = usr/bin# Relative to root directory in target file system.

include common/common.mk
