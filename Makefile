EXECUTABLE_NAME = red_black_tree
PROJECT_ROOT_DIR = $(shell pwd)
SRC_DIR = "$(PROJECT_ROOT_DIR)/src"
BUILD_SUB_DIR = "$(PROJECT_ROOT_DIR)/build"
OUTPUT_SUB_DIR = "$(PROJECT_ROOT_DIR)/bin"
BUILD_DIR = "$(BUILD_SUB_DIR)/$(TARGET_ARCH)"
OUTPUT_DIR = "$(PROJECT_ROOT_DIR)/bin"

CMAKE = cmake $(SRC_DIR) \
	-DCOMPILER=$(COMPILER)

.PHONY all: x86_64
.PHONY x86_64: build

build:
	@echo "Build started"
	@echo "cmake: $(CMAKE)"
	@mkdir -p $(BUILD_DIR) && \
		cd $(BUILD_DIR) && \
		$(CMAKE) && \
		make && \
		mkdir -p $(OUTPUT_DIR) && \
		mv $(EXECUTABLE_NAME) $(OUTPUT_DIR)/$(EXECUTABLE_NAME)

clean:
	@rm -rf $(BUILD_SUB_DIR)
	@rm -rf $(OUTPUT_SUB_DIR)

help:
	@echo
	@echo "  make [target]"
	@echo
	@echo " Targets:"
	@echo "    all		Builds the project for x86_64"
	@echo "    x86_64	Builds the project for x86_64"
	@echo "    clean	Removes build and output folders"
	@echo "    help	Prints this help message"