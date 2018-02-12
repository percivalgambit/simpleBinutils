include make/*.mk

ifdef MEMORY_SIZE
CPPFLAGS += -DMEMORY_SIZE="$(MEMORY_SIZE)"
endif
ifdef WORD_SIZE
CPPFLAGS += -DWORD_SIZE="$(WORD_SIZE)"
endif

PANIC_SRC := src/util/panic.cc
STATUS_SRC := src/util/status.cc
WORD_STREAM_SRC := src/test_util/word_stream.cc
MEMORY_SRC := src/emulator/memory.cc $(PANIC_SRC) $(STATUS_SRC)
DECODE_INSTRUCTION_SRC := src/emulator/decode_instruction.cc $(PANIC_SRC) $(MEMORY_SRC)
EMULATOR_SRC := src/emulator/emulator.cc $(PANIC_SRC) $(STATUS_SRC) $(MEMORY_SRC) $(DECODE_INSTRUCTION_SRC)
SIMPLEEMU_SRC := src/emulator/main.cc $(STATUS_SRC) $(EMULATOR_SRC)

GEN_HELLO_PROG_SRC := src/emulator/integration/test/gen_hello_prog.cc
GEN_HELLO_PROG_BIN := obj/test/integration_test/bin/gen_hello_prog

$(eval $(call binary,simpleEMU,$(SIMPLEEMU_SRC)))
$(eval $(call debug_binary,simpleEMU-debug,$(SIMPLEEMU_SRC)))

$(eval $(call unit_test,status_test,$(STATUS_SRC) src/util/status_test.cc))
$(eval $(call unit_test,statusor_test,$(PANIC_SRC) $(STATUS_SRC) src/util/statusor_test.cc))
$(eval $(call unit_test,memory_test,$(MEMORY_SRC) $(WORD_STREAM_SRC) src/emulator/memory_test.cc))
$(eval $(call unit_test,decode_instruction_test,$(DECODE_INSTRUCTION_SRC) $(WORD_STREAM_SRC) src/emulator/decode_instruction_test.cc))
$(eval $(call unit_test,emulator_test,$(EMULATOR_SRC) $(WORD_STREAM_SRC) src/emulator/emulator_test.cc))

$(eval $(call debug_binary,$(GEN_HELLO_PROG_BIN),$(WORD_STREAM_SRC) $(GEN_HELLO_PROG_SRC)))
$(eval $(call generate_file,obj/integration_test/input/emulator_hello_prog.bin,$(GEN_HELLO_PROG_BIN)))

emulator_hello_prog.integration_test: SUT := simpleEMU-debug
emulator_hello_prog.integration_test: REFERENCE_FILES := src/emulator/integration/reference/emulator_hello_prog.stdout.reference src/emulator/integration/reference/emulator_hello_prog.stderr.reference
$(eval $(call integration_test,emulator_hello_prog))
