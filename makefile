# Global configuration
MAKEFLAGS += --no-print-directory

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Targets
.PHONY: all
all:
	@echo "Building"
	@$(MAKE) -C $(SRC_DIR)
	@$(MAKE) -C $(TEST_DIR)

.PHONY: test
test:
	@echo "Building tests"
	@$(MAKE) -C $(TEST_DIR) test


.PHONY: clean
clean:
	@echo "Cleaning"
	@$(MAKE) -C $(SRC_DIR) clean
	@$(MAKE) -C $(TEST_DIR) clean
	@rm -rf $(BUILD_DIR)