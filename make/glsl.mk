GLSLC = glslc

VERT_SRCS := $(shell find -L $(ROOTDIR)/src -name "*.vert")
FRAG_SRCS := $(shell find -L $(ROOTDIR)/src -name "*.frag")
GLSL_SRCS := $(shell find -L $(ROOTDIR)/src -name "*.glsl")

.PHONY: shaders
shaders :                                                                    \
  $(patsubst $(ROOTDIR)/src/%.vert, $(ROOTDIR)/spv/vert/%.spv, $(VERT_SRCS)) \
  $(patsubst $(ROOTDIR)/src/%.frag, $(ROOTDIR)/spv/frag/%.spv, $(FRAG_SRCS)) \
  $(patsubst $(ROOTDIR)/src/%.glsl, $(ROOTDIR)/spv/glsl/%.spv, $(GLSL_SRCS))
	@echo "shaders build success!"

$(ROOTDIR)/spv/frag/%.spv: $(ROOTDIR)/src/%.frag
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@ 

$(ROOTDIR)/spv/vert/%.spv: $(ROOTDIR)/src/%.vert
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@

$(ROOTDIR)/spv/glsl/%.spv: $(ROOTDIR)/src/%.glsl
	@mkdir -p $(@D)
	@$(GLSLC) $< -o $@
