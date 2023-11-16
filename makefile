PROGRAM = MangosRenderEngine

BINDIR = .bin
OBJDIR = $(BINDIR)/obj
DEPDIR = $(BINDIR)/dep
EXEDIR = $(BINDIR)

INCLUDES := $(shell find -L $(CURDIR) -name "include")
HEADERS  := $(shell find -L $(CURDIR) -name "*.hpp")
SRCS     := $(shell find -L $(CURDIR) -name "*.cpp")
OBJS      = $(patsubst $(CURDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS      = $(patsubst $(CURDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))

CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -O
CPPFLAGS = `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(INCLUDES))
LDLIBS   = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

CLANGFORMATFLAGS = -i -style=file
CLANGTIDYFLAGS   = -checks=-*,performance*,portability*,concurrency*,clang-analyzer*,cppcoreguidelines*

.PHONY: all
all: $(EXEDIR)/$(PROGRAM)
	@clang-format $(HEADERS) $(SRCS) $(CLANGFORMATFLAGS)
	@clang-tidy $(HEADERS) $(SRCS) $(CLANGTIDYFLAGS)
	@echo "Build succsess!"

.PHONY: format
run:
	@clang-format $(HEADERS) $(SRCS) $(CLANGFORMATFLAGS)

.PHONY: tidy
run:
	@clang-tidy $(HEADERS) $(SRCS) $(CLANGTIDYFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BINDIR)
	@echo "Clean succsess!"

$(EXEDIR)/$(PROGRAM): $(OBJS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(DEPDIR)/%.d, $(OBJDIR)/%.o, $@) -o $@

-include $(DEPS)
