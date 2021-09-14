#!/bin/sh

SOURCES=$(find src -name "*.cpp" -or -name "*.h")
INCLUDES=$(find include -name "*.cpp" -or -name "*.h")
clang-format -vi $SOURCES $INCLUDES
