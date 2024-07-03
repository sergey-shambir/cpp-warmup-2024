all: conan cmake build test

conan:
	conan install . --build=missing --profile=debug

cmake:
	cmake CMakeLists.txt -Bbuild/Debug -DCMAKE_TOOLCHAIN_FILE="generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug

build:
	cmake --build build/Debug

test: build
	bin/01_sqrt
	bin/02_eratosthenes
	bin/03_hash_table
	bin/04_flat_map
	bin/05_avl_tree_map
	bin/06_sparce_graph
	bin/07_dinning_philosophers

.PHONY: conan cmake build test
