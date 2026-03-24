.PHONY: clean config build re asan macos_sym

BUILD_DIR=build
BUILD_TYPE?=Debug

clean:
	@rm -rf "$(BUILD_DIR)" && mkdir -p "$(BUILD_DIR)"

config:
	@cmake -S . -B "$(BUILD_DIR)" --fresh -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build:
	@cmake --build "$(BUILD_DIR)"

asan:
	@cmake -S . -B "$(BUILD_DIR)" -DCMAKE_BUILD_TYPE=Debug -DASAN=1
	@cmake --build "$(BUILD_DIR)"
	@ASAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=suppressions=asan.supp ./build/Debug/wolf3d ./data/map/demo.w3d &> asan.out

macos_sym:
	dsymutil ./build/Debug/wolf3d
	strip -x ./build/Debug/wolf3d

re: clean config build

