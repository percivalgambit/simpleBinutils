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
LDLIBS := -lm

###### Objects' build rules ######

# Defines the location of source and object files.
OBJS := $(patsubst src/%.cc,obj/%.o,$(wildcard src/*.cc))

obj:
	@mkdir -p $@

# Default rule to build a C object.
obj/%.o: src/%.cc | $$(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

obj/tests/%.o: tests/unit_tests/%.cc | obj/tests
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

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

UNIT_TESTS :=

obj/tests:
	@mkdir -p $@

unit_test: CPPFLAGS += -UNDEBUG
unit_test: CXXFLAGS += -O0 -ggdb3
unit_test: $(UNIT_TESTS:%=obj/tests/%)
	@echo "All unit tests passed"

$(UNIT_TESTS:%=obj/tests/%): | obj/tests
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)
	./$@

###### Special unit test parameters ######
obj/tests/big_int_test: obj/tests/big_int_test.o

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

