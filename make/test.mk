# TODO: make it possible to rerun unit tests without having to make clean
define unit_test =
unit_test: obj/unit_test/$(1)
obj/unit_test/$(1): $(call debug_objects,$(2)) $(call test_objects,$(3)) obj/test/catch_main.o
	@mkdir -p $$(@D)
	$(CXX) $(LDFLAGS) $$^ -o $$@ $(LOADLIBES) $(LDLIBS)
	./$$@
endef

define integration_test =
_test_name := obj/integration_test/$(1).tested

integration_test: $$(_test_name)
$$(_test_name):
	@mkdir -p $$(@D)
	$(MAKE) $(1).test
	@touch $$@
endef

.SECONDEXPANSION:

%.test: SUT             =
%.test: INPUT_PROG      = obj/integration_test/prog/$(@:%.test=%).bin
%.test: SHOULD_FAIL     =
%.test: EXPECTED_STDOUT = test/integration/reference/$(@:.test=.stdout.reference)
%.test: EXPECTED_STDERR = test/integration/reference/$(@:.test=.stderr.reference)
%.test: ACTUAL_STDOUT   = obj/integration_test/out/$(@:.test=.stdout)
%.test: ACTUAL_STDERR   = obj/integration_test/out/$(@:.test=.stderr)
%.test: $$(SUT) $$(INPUT_PROG)
	@mkdir -p $(dir $(ACTUAL_STDOUT))
	@mkdir -p $(dir $(ACTUAL_STDERR))
	$(if $(SHOULD_FAIL),-) ./$< $(INPUT_PROG) > $(ACTUAL_STDOUT) 2> $(ACTUAL_STDERR)
	diff $(ACTUAL_STDOUT) $(EXPECTED_STDOUT)
	diff $(ACTUAL_STDERR) $(EXPECTED_STDERR)

.PHONY: test unit_test integration_test

test: unit_test integration_test
	@echo "All tests passed"

unit_test:
	@echo "All unit tests passed"

integration_test:
	@echo "All integration tests passed"
