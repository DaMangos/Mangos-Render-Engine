PROGRAM = MangosRenderEngine

OBJDIR = $(CURDIR)/obj
DEPDIR = $(CURDIR)/dep
EXEDIR = $(CURDIR)/bin

INCLUDES        := $(shell find -L $(CURDIR) -name "include")
HEADERS         := $(shell find -L $(CURDIR) -name "*.hpp")
IMPLEMENTATIONS := $(shell find -L $(CURDIR) -name "*.ipp")
SRCS            := $(shell find -L $(CURDIR) -name "*.cpp")
OBJS             = $(patsubst $(CURDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS             = $(patsubst $(CURDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))

CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -O
CPPFLAGS = `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(INCLUDES))
LDLIBS   = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

CLANGFORMATFLAGS = -i -style=file

.PHONY: all
all: format compile_commands

.PHONY: build
build: $(EXEDIR)/$(PROGRAM)
	@echo "build success!"

.PHONY: format
format:
	@clang-format $(HEADERS) $(IMPLEMENTATIONS) $(SRCS) $(CLANGFORMATFLAGS)
	@echo "format success!"

.PHONY: compile_commands
compile_commands:
	@bear -- make build
	@echo "compile commands success!"

.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)
	@rm -rf $(EXEDIR)
	@rm -rf .cache compile_commands.json
	@echo "clean success!"

$(EXEDIR)/$(PROGRAM): $(OBJS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(DEPDIR)/%.d, $(OBJDIR)/%.o, $@) -o $@

-include $(DEPS)
