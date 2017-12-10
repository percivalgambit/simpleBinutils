all: simpleEMU

# Sets useful options for make
.PHONY: all clean test unit_test integration_test
.DELETE_ON_ERROR:
.SECONDEXPANSION:

##############################################################
#
# Build rules
#
##############################################################

# Defines variables used in recipes to build the main application.
SHELL := /bin/bash
CXX := g++
#CPPFLAGS := -DNDEBUG
CXXFLAGS := -std=gnu++17 -pedantic-errors -Wall -Wextra -Werror -march=native -O3 -MMD -MP -Isrc/
LDLIBS :=

###### Objects' build rules ######

# Defines the location of source and object files.
COMMON_OBJS := $(patsubst src/common/%.cc,obj/common/%.o,$(wildcard src/common/*.cc))
EMULATOR_OBJS := $(patsubst src/emulator/%.cc,obj/emulator/%.o,$(wildcard src/emulator/*.cc))
UTIL_OBJS := $(patsubst src/util/%.cc,obj/util/%.o,$(wildcard src/util/*.cc))
OBJS := $(COMMON_OBJS) $(EMULATOR_OBJS) $(UTIL_OBJS)

# Default rule to build a C object.
obj/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

obj/tests/%.o: tests/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Itests -c $< -o $@

# Tracks header dependencies for future recompilation.
obj/%.d: %.cc
-include obj/*/*.d

###### Applications' build rules ######

simpleEMU: $(OBJS)
	$(CXX) $(LDFLAGS) $(filter %.o,$^) -o $@ $(LOADLIBES) $(LDLIBS)

###### Special target rules ######

clean:
	$(RM) -r obj/ simpleEMU

test: unit_test integration_test
	@echo "All tests passed"

##############################################################
#
# Correctness tests
#
##############################################################

###### Unit tests ######

UNIT_TESTS := util/status_test util/statusor_test emulator/accumulator_test emulator/memory_test

unit_test: CPPFLAGS += -UNDEBUG
unit_test: CXXFLAGS += -O0 -ggdb3
unit_test: $(UNIT_TESTS:%=obj/tests/%)
	@echo "All unit tests passed"

$(UNIT_TESTS:%=obj/tests/%):
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)
	./$@


###### Special unit test parameters ######
obj/tests/util/status_test: obj/util/status.o obj/tests/util/status_test.o
obj/tests/util/statusor_test: obj/util/status.o obj/tests/util/statusor_test.o
obj/tests/emulator/accumulator_test: obj/tests/emulator/accumulator_test.o
obj/tests/emulator/memory_test: obj/util/status.o obj/emulator/memory.o obj/tests/emulator/memory_test.o

###### Integration tests ######

INTEGRATION_TESTS :=

integration_test: $(INTEGRATION_TESTS:%=test_output/%.tested)
	@echo "All integration tests passed"

test_output:
	@mkdir -p $@

%.tested: | $$(@D)
	$(MAKE) $(@:test_output/%.tested=%.test)
	@touch $@

# Default correctness test rule
%.test:

###### Special integration test parameters ######

