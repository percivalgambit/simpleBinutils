SHELL := /bin/bash
CXX := g++
CXXFLAGS := -std=gnu++17 -pedantic-errors -Wall -Wextra -Werror -march=native -MMD -MP -Isrc/

RELEASE_CPPFLAGS := -DNDEBUG
RELEASE_CXXFLAGS := -O3

DEBUG_CPPFLAGS := -DDEBUG
DEBUG_CXXFLAGS := -O0 -g
