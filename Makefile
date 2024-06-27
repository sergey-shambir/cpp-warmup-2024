all: conan cmake build test

conan:
	conan install . --build=missing

cmake:
	cmake CMakeLists.txt -Bbuild/Release -DCMAKE_TOOLCHAIN_FILE="generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release

build:
	cmake --build build/Release

test: build
	bin/01_sqrt
	bin/02_eratosthenes
	bin/03_hash_table

.PHONY: conan cmake build test
