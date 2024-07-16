EXE = MangosRenderEngine

CXX           = clang++
GLSLC         = glslc -O

CXXFLAGS      = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -O
CPPFLAGS      = `pkg-config --cflags gtest_main` `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(shell find -L $(CURDIR) -name "include"))
LDLIBS        = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

SRCS      := $(shell find -L $(CURDIR)/src -name "*.cpp" -not -path "*/test/*")
TEST_SRCS := $(shell find -L $(CURDIR)/src -name "*.cpp" -not -path "*/main.cpp")
VERT_SRCS := $(shell find -L $(CURDIR)/src -name "*.vert")
FRAG_SRCS := $(shell find -L $(CURDIR)/src -name "*.frag")
GLSL_SRCS := $(shell find -L $(CURDIR)/src -name "*.glsl")

DEBUG_CXXFLAGS   = $(CXXFLAGS) -UNDEBUG -g
RELEASE_CXXFLAGS = $(CXXFLAGS) -DNDEBUG
TEST_LDLIBS      = $(LDLIBS) `pkg-config --static --libs gtest_main`

.PHONY: all
all: format compile_commands shaders debug release test

.PHONY: shaders
shaders : \
  $(patsubst $(CURDIR)/src/%.vert, $(CURDIR)/spv/vert/%.spv, $(VERT_SRCS)) \
  $(patsubst $(CURDIR)/src/%.frag, $(CURDIR)/spv/frag/%.spv, $(FRAG_SRCS)) \
  $(patsubst $(CURDIR)/src/%.glsl, $(CURDIR)/spv/glsl/%.spv, $(GLSL_SRCS))
	@echo "shaders build success!"

.PHONY: format
format:
	@clang-format $(shell find -L $(CURDIR) -name "*.cpp" -o -name "*.hpp" -o -name "*.ipp" -o -name "*.frag" -o -name "*.vert" -o -name "*.glsl") -style=file -i
	@echo "format success!"

.PHONY: compile_commands
compile_commands :
	@bear -- make $(CURDIR)/bin/debug/$(EXE) $(CURDIR)/bin/release/$(EXE) $(CURDIR)/bin/test/$(EXE)
	@echo "compile commands success!"

.PHONY: debug
debug: $(CURDIR)/bin/debug/$(EXE)
	@echo "debug build success!"

.PHONY: release
release: $(CURDIR)/bin/release/$(EXE)
	@echo "release build success!"

.PHONY: test
test: $(CURDIR)/bin/test/$(EXE)
	@echo "test build success!"
	@$(CURDIR)/bin/test/$(EXE)

.PHONY: clean
clean:
	@rm -rf $(CURDIR)/spv $(CURDIR)/bin $(CURDIR)/dep $(CURDIR)/obj $(CURDIR)/compile_commands.json
	@echo "clean success!"


$(CURDIR)/spv/frag/%.spv: $(CURDIR)/src/%.frag
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@

$(CURDIR)/spv/vert/%.spv: $(CURDIR)/src/%.vert
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@

$(CURDIR)/spv/glsl/%.spv: $(CURDIR)/src/%.glsl
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@


$(CURDIR)/bin/debug/$(EXE): $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/obj/debug/%.o, $(SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) -o $@ $^ $(LDLIBS)

$(CURDIR)/bin/release/$(EXE): $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/obj/release/%.o, $(SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(RELEASE_CXXFLAGS) -o $@ $^ $(LDLIBS)

$(CURDIR)/bin/test/$(EXE): $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/obj/test/%.o, $(TEST_SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) -o $@ $^ $(TEST_LDLIBS)


$(CURDIR)/obj/debug/%.o: $(CURDIR)/src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(CURDIR)/obj/release/%.o: $(CURDIR)/src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(RELEASE_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(CURDIR)/obj/test/%.o: $(CURDIR)/src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<


$(CURDIR)/dep/debug/%.d: $(CURDIR)/src/%.cpp
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/debug/%.d, $(CURDIR)/obj/debug/%.o, $@) -o $@

$(CURDIR)/dep/release/%.d: $(CURDIR)/src/%.cpp
	@$(CXX) $(RELEASE_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/release/%.d, $(CURDIR)/obj/release/%.o, $@) -o $@

$(CURDIR)/dep/test/%.d: $(CURDIR)/src/%.cpp
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/test/%.d, $(CURDIR)/obj/test/%.o, $@) -o $@


-include $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/dep/debug/%.d, $(SRCS)) 
-include $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/dep/release/%.d, $(SRCS)) 
-include $(patsubst $(CURDIR)/src/%.cpp, $(CURDIR)/dep/test/%.d, $(TEST_SRCS))
