objects = $(patsubst src/%.cc,obj/release/%.o,$(sort $(1)))
debug_objects = $(patsubst src/%.cc,obj/debug/%.o,$(sort $(1)))
test_objects = $(patsubst test/%.cc,obj/test/%.o,$(sort $(1)))

obj/release/%.o: CPPFLAGS += $(RELEASE_CPPFLAGS)
obj/release/%.o: CXXFLAGS += $(RELEASE_CXXFLAGS)
obj/release/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

obj/debug/%.o: CPPFLAGS += $(DEBUG_CPPFLAGS)
obj/debug/%.o: CXXFLAGS += $(DEBUG_CXXFLAGS)
obj/debug/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

obj/test/%.o: CPPFLAGS += $(TEST_CPPFLAGS)
obj/test/%.o: CXXFLAGS += $(TEST_CXXFLAGS)
obj/test/%.o: test/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

obj/release/%.d: src/%.cc
obj/debug/%.d: src/%.cc
include $(shell [[ -e obj/ ]] && find obj/ -type f -name "*.d")
