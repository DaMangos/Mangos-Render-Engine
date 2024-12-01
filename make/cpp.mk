EXE = MangosRenderEngine

CXX = clang++

CPP_FLAGS =                                                         \
	$(patsubst %, -I%, $(shell find -L $(ROOTDIR) -name "include")) \
	`pkg-config --cflags vulkan`                                    \
	`pkg-config --cflags glfw3`                                     \
	`pkg-config --cflags gtest_main`                                \
	-DGLFW_INCLUDE_VULKAN                                           \
	-DVULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1                          \
	-DVULKAN_HPP_NO_STRUCT_CONSTRUCTORS                             \
	-DVULKAN_HPP_NO_STRUCT_SETTERS                                  \
	-DVK_ENABLE_BETA_EXTENSIONS

CXX_FLAGS =      \
	-std=c++20   \
	-O3          \
	-Wall        \
	-Wextra      \
	-Wpedantic   \
	-Wshadow     \
	-Wconversion \
	-Werror

LDLIBS =                                \
	`pkg-config --static --libs vulkan` \
	`pkg-config --static --libs glfw3`  \

ifeq ($(BUILD_MODE), debug)
	SRCS := $(shell find -L $(ROOTDIR)/src -name "*.cpp" -not -path "*/test/*")
	CXX_FLAGS += -UNDEBUG -g
endif 

ifeq ($(BUILD_MODE), release)
	SRCS := $(shell find -L $(ROOTDIR)/src -name "*.cpp" -not -path "*/test/*")
	CXX_FLAGS += -DNDEBUG
endif

ifeq ($(BUILD_MODE), test)
	SRCS := $(shell find -L $(ROOTDIR)/src -name "*.cpp" -not -path "*/main.cpp")
	CXX_FLAGS += -UNDEBUG -g
	LDLIBS += `pkg-config --static --libs gtest_main`
endif

.PHONY: $(BUILD_MODE)
$(BUILD_MODE): $(ROOTDIR)/bin/$(BUILD_MODE)/$(EXE)
	@echo $(BUILD_MODE) build success!

$(ROOTDIR)/bin/$(BUILD_MODE)/$(EXE): $(patsubst $(ROOTDIR)/src/%.cpp, $(ROOTDIR)/obj/$(BUILD_MODE)/%.o, $(SRCS))
	@mkdir -p $(@D)
	@$(CXX) $(CPP_FLAGS) -o $@ $^ $(LDLIBS)

$(ROOTDIR)/obj/$(BUILD_MODE)/%.o: $(ROOTDIR)/src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -o $@ -c $<

$(ROOTDIR)/dep/$(BUILD_MODE)/%.d: $(ROOTDIR)/src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) $< -MM -MT $(patsubst $(ROOTDIR)/dep/$(BUILD_MODE)/%.d, $(ROOTDIR)/obj/$(BUILD_MODE)/%.o, $@) -o $@

-include $(patsubst $(ROOTDIR)/src/%.cpp, $(ROOTDIR)/dep/$(BUILD_MODE)/%.d, $(SRCS)) 
