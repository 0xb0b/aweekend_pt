BUILD_DIR := .build

.PHONY: clean main tests

main:
	make -f main.mk

tests:
	make -f tests.mk

clean:
	@rm -rf $(BUILD_DIR)

