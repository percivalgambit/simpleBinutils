include make/*.mk

ifdef MEMORY_SIZE
CPPFLAGS += -DMEMORY_SIZE="$(MEMORY_SIZE)"
endif
ifdef WORD_SIZE
CPPFLAGS += -DWORD_SIZE="$(WORD_SIZE)"
endif

STATUS_SRC := src/util/status.cc
MEMORY_SRC := src/emulator/memory.cc $(STATUS_SRC)
DECODE_INSTRUCTION_SRC := src/emulator/decode_instruction.cc $(MEMORY_SRC)
EMULATOR_SRC := src/emulator/emulator.cc $(STATUS_SRC) $(MEMORY_SRC) $(DECODE_INSTRUCTION_SRC)
SIMPLEEMU_SRC := src/emulator/main.cc $(STATUS_SRC) $(EMULATOR_SRC)

GEN_HELLO_PROG_SRC := test/integration/emulator/gen_hello_prog.cc
GEN_HELLO_PROG_BIN := obj/integration_test/bin/gen_hello_prog

$(eval $(call binary,simpleEMU,$(SIMPLEEMU_SRC)))
$(eval $(call debug_binary,simpleEMU-debug,$(SIMPLEEMU_SRC)))

$(eval $(call unit_test,status_test,$(STATUS_SRC),test/util/status_test.cc))
$(eval $(call unit_test,statusor_test,$(STATUS_SRC),test/util/statusor_test.cc))
$(eval $(call unit_test,memory_test,$(MEMORY_SRC),test/emulator/memory_test.cc))
$(eval $(call unit_test,decode_instruction_test,$(DECODE_INSTRUCTION_SRC),test/emulator/decode_instruction_test.cc))
$(eval $(call unit_test,emulator_test,$(EMULATOR_SRC),test/emulator/emulator_test.cc))

$(eval $(call debug_binary,$(GEN_HELLO_PROG_BIN),,$(GEN_HELLO_PROG_SRC)))
$(eval $(call generate_file,obj/integration_test/prog/emulator_hello_prog.bin,$(GEN_HELLO_PROG_BIN)))

emulator_hello_prog.test: SUT := simpleEMU-debug
$(eval $(call integration_test,emulator_hello_prog))
