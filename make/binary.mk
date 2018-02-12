define binary =
all: $(1)
CLEAN_ITEMS += $(filter-out obj/%,$(1))
$(1): $(call objects,$(2))
	@mkdir -p $$(@D)
	$(CXX) $(LDFLAGS) $$^ -o $$@ $(LOADLIBES) $(LDLIBS)
endef

define debug_binary =
CLEAN_ITEMS += $(filter-out obj/%,$(1))
$(1): $(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$(CXX) $(LDFLAGS) $$^ -o $$@ $(LOADLIBES) $(LDLIBS)
endef
