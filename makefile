PROGRAM = MangosGameEngine.app

BINDIR    = bin
OBJDIR    = $(BINDIR)/obj
DEPDIR    = $(BINDIR)/dep
EXEDIR    = $(BINDIR)/exe

INCLUDES := $(shell find -L $(CURDIR) -name "include")
SRCS     := $(shell find -L $(CURDIR) -name "*.cpp")
OBJS      = $(patsubst $(CURDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS      = $(patsubst $(CURDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))

CXX       = clang++
CXXFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror
CPPFLAGS  = `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(INCLUDES))
LDLIBS    = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

target debug   : CPPFLAGS += -D DEBUG=1
traget release : CXXFLAGS += -O

.PHONY: defualt
defualt: $(EXEDIR)/$(PROGRAM)

.PHONY: debug
debug: defualt

.PHONY: release
release: defualt

.PHONY: run
run: defualt
	@$(EXEDIR)/$(PROGRAM)

.PHONY: clean
clean:
	@rm -rf $(BINDIR)

.PHONY: clean-clangd
clean-clangd:
	@rm -rf .cache
	@rm -rf compile_commands.json

.PHONY: clangd
clangd:
	@make clean
	@make clean-clangd
	@bear -- make

$(EXEDIR)/$(PROGRAM): $(OBJS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(DEPDIR)/%.d, $(OBJDIR)/%.o, $@) -o $@

-include $(DEPS)