define test =
_test_marker := obj/test/$(2)/tested/$(1).tested

.PHONY: $(1) $(1).$(2)
$(2): $(1)
$(1): $$(_test_marker)
$$(_test_marker): $(1).$(2)
	@mkdir -p $$(@D)
	@touch $$@
endef

define unit_test =
_test_name := obj/test/unit_test/bin/$(1)

$$(eval $$(call test,$(1),unit_test))

$(1).unit_test: $$(_test_name)
$$(_test_name): obj/debug/test_util/catch_main.o $(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$(CXX) $(LDFLAGS) $$^ -o $$@ $(LOADLIBES) $(LDLIBS)
ifdef DEBUG_CMD
	$(DEBUG_CMD) ./$$@
	@false
else
	./$$@
endif
endef

define integration_test =
$$(eval $$(call test,$(1),integration_test))

$(1).integration_test: SUT             ?=
$(1).integration_test: INPUT_PROG      ?= obj/integration_test/input/$$(@:%.integration_test=%).bin
$(1).integration_test: SHOULD_FAIL     ?=
$(1).integration_test: EXPECTED_STDOUT ?= $(INTEGRATION_REFERENCE_DIR)/$$(@:.integration_test=.stdout.reference)
$(1).integration_test: EXPECTED_STDERR ?= $(INTEGRATION_REFERENCE_DIR)/$$(@:.integration_test=.stderr.reference)
$(1).integration_test: ACTUAL_STDOUT   ?= obj/integration_test/output/$$(@:.integration_test=.stdout)
$(1).integration_test: ACTUAL_STDERR   ?= obj/integration_test/output/$$(@:.integration_test=.stderr)
$(1).integration_test: REFERENCE_FILES ?=
$(1).integration_test: $$$$(SUT) $$$$(INPUT_PROG)
	@mkdir -p $$(dir $$(ACTUAL_STDOUT))
	@mkdir -p $$(dir $$(ACTUAL_STDERR))
	@mkdir -p $(INTEGRATION_REFERENCE_DIR)
	-cp $$(REFERENCE_FILES) $(INTEGRATION_REFERENCE_DIR)
	$$(if $$(SHOULD_FAIL),-) $(DEBUG_CMD) ./$$< $$(INPUT_PROG) > $$(ACTUAL_STDOUT) 2> $$(ACTUAL_STDERR)
	diff $$(ACTUAL_STDOUT) $$(EXPECTED_STDOUT)
	diff $$(ACTUAL_STDERR) $$(EXPECTED_STDERR)
endef

INTEGRATION_REFERENCE_DIR := obj/integration_test/reference

.PHONY: test unit_test integration_test

test: unit_test integration_test
	@echo "All tests passed"

unit_test:
	@echo "All unit tests passed"

integration_test:
	@echo "All integration tests passed"
