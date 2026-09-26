SHELL := /bin/sh

BUILD_DIR := build
CMAKE_BUILD_TYPE ?= Release

.DEFAULT_GOAL := help
.PHONY: help configure build run clean package-linux package

help: ## Show available commands.
	@awk 'BEGIN {FS = ":.*##"}; /^[a-zA-Z_-]+:.*##/ {printf "  %-16s %s\n", $$1, $$2}' $(MAKEFILE_LIST)

configure: ## Configure a local CMake build (use CMAKE_BUILD_TYPE=Debug for debug).
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

build: configure ## Build the game locally.
	cmake --build $(BUILD_DIR) --parallel

run: build ## Build and run the game locally.
	cd $(BUILD_DIR) && ./asteroids

clean: ## Remove the local CMake build directory.
	rm -rf $(BUILD_DIR)

package-linux: ## Generate dist/linux/asteroids-linux-x86_64.zip using Docker.
	docker build --target package-linux --output type=local,dest=dist/linux .

package: package-linux ## Generate the Linux distributable ZIP using Docker.
