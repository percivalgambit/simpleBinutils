define generate_file =
CLEAN_ITEMS += $(filter-out obj/%,$(1))
$(1): $(2)
	@mkdir -p $$(@D)
	./$$< > $$@
endef
