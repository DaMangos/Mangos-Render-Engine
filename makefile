EXE = MangosRenderEngine

ROOTDIR = $(CURDIR)

.PHONY: all
all: compile_commands format shaders debug release test

.PHONY: format
format:
	@clang-format $(shell find -L $(ROOTDIR) -name "*.cpp" -o -name "*.hpp" -o -name "*.ipp" -o -name "*.frag" -o -name "*.vert" -o -name "*.glsl") -style=file -i

.PHONY: compile_commands
compile_commands :
	@rm -rf $(ROOTDIR)/compile_commands.json
	@bear -- make -f $(ROOTDIR)/make/cpp.mk --warn-undefined-variables ROOTDIR="$(ROOTDIR)" BUILD_MODE="debug"

.PHONY: debug
debug:
	@make -f $(ROOTDIR)/make/cpp.mk --warn-undefined-variables ROOTDIR="$(ROOTDIR)" BUILD_MODE="debug"

.PHONY: release
release:
	@make -f $(ROOTDIR)/make/cpp.mk --warn-undefined-variables ROOTDIR="$(ROOTDIR)" BUILD_MODE="release"

.PHONY: test
test: 
	@make -f $(ROOTDIR)/make/cpp.mk --warn-undefined-variables ROOTDIR="$(ROOTDIR)" BUILD_MODE="test"

.PHONY: shaders
shaders :
	@make -f $(ROOTDIR)/make/glsl.mk --warn-undefined-variables ROOTDIR="$(ROOTDIR)"

.PHONY: clean
clean:
	@rm -rf $(ROOTDIR)/spv $(ROOTDIR)/bin $(ROOTDIR)/dep $(ROOTDIR)/obj $(ROOTDIR)/log $(ROOTDIR)/compile_commands.json
	@echo "clean success!"
