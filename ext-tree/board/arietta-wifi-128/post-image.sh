#!/bin/bash

SCRIPT_PATH=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")
PROJECT_DIR=$(readlink -m "$SCRIPT_DIR"/../../../)

# Copy the sdcard image to the project directory.
echo Copying "${BINARIES_DIR}"/sdcard.img to "$PROJECT_DIR."
cp "${BINARIES_DIR}"/sdcard.img "$PROJECT_DIR"
