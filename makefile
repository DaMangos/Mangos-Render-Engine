PROGRAM = MangosGameEngine

BINDIR    = .bin
OBJDIR    = $(BINDIR)/obj
DEPDIR    = $(BINDIR)/dep
EXEDIR    = $(BINDIR)

INCLUDES := $(shell find -L $(CURDIR) -name "include")
SRCS     := $(shell find -L $(CURDIR) -name "*.cpp")
OBJS      = $(patsubst $(CURDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS      = $(patsubst $(CURDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCS))

CXX       = clang++
CXXFLAGS  = -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -O
CPPFLAGS  = `pkg-config --cflags glfw3` `pkg-config --cflags vulkan` $(patsubst %, -I%, $(INCLUDES))
LDLIBS    = `pkg-config --static --libs glfw3` `pkg-config --static --libs vulkan`

target debug   : CPPFLAGS += -D DEBUG=1

.PHONY: debug
debug: $(EXEDIR)/$(PROGRAM)

.PHONY: release
release: $(EXEDIR)/$(PROGRAM)

.PHONY: run
run: $(EXEDIR)/$(PROGRAM)
	@$<

.PHONY: clean
clean:
	@rm -rf $(BINDIR)

$(EXEDIR)/$(PROGRAM): $(OBJS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(CURDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(CURDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -MM -MT $(patsubst $(DEPDIR)/%.d, $(OBJDIR)/%.o, $@) -o $@

-include $(DEPS)