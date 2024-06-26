EXE = MangosRenderEngine

CXX           = clang++
CXXFLAGS      = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -O
CPPFLAGS      = `pkg-config --cflags gtest_main` `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(shell find -L $(CURDIR) -name "include"))
LDLIBS        = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

SRCS      := $(shell find -L $(CURDIR) -name "*.cpp" -not -path "*/test/*")
TEST_SRCS := $(shell find -L $(CURDIR) -name "*.cpp" -not -path "*/main.cpp")

DEBUG_CXXFLAGS   = $(CXXFLAGS) -UNDEBUG -g
RELEASE_CXXFLAGS = $(CXXFLAGS) -DNDEBUG
TEST_LDLIBS      = $(LDLIBS) `pkg-config --static --libs gtest_main`

.PHONY: all
all: format compile_commands debug release test

.PHONY: format
format:
	@clang-format $(shell find -L $(CURDIR) -name "*.cpp" -o -name "*.hpp" -o -name "*.ipp") -style=file -i
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
	@rm -rf $(CURDIR)/bin $(CURDIR)/dep $(CURDIR)/obj $(CURDIR)/compile_commands.json
	@echo "clean success!"


$(CURDIR)/bin/debug/$(EXE): $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/obj/debug/%.o, $(SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) -o $@ $^ $(LDLIBS)

$(CURDIR)/bin/release/$(EXE): $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/obj/release/%.o, $(SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(RELEASE_CXXFLAGS) -o $@ $^ $(LDLIBS)

$(CURDIR)/bin/test/$(EXE): $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/obj/test/%.o, $(TEST_SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) -o $@ $^ $(TEST_LDLIBS)



$(CURDIR)/obj/debug/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(CURDIR)/obj/release/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(RELEASE_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(CURDIR)/obj/test/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) -o $@ -c $<



$(CURDIR)/dep/debug/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/debug/%.d, $(CURDIR)/obj/debug/%.o, $@) -o $@

$(CURDIR)/dep/release/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(RELEASE_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/release/%.d, $(CURDIR)/obj/release/%.o, $@) -o $@

$(CURDIR)/dep/test/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(DEBUG_CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(CURDIR)/dep/test/%.d, $(CURDIR)/obj/test/%.o, $@) -o $@



-include $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/dep/debug/%.d, $(SRCS)) 
-include $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/dep/release/%.d, $(SRCS)) 
-include $(patsubst $(CURDIR)/%.cpp, $(CURDIR)/dep/test/%.d, $(TEST_SRCS))
