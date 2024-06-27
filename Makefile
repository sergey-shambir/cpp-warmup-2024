all: conan cmake build

conan:
	conan install . --build=missing

cmake:
	cmake CMakeLists.txt -Bbuild/Release -DCMAKE_TOOLCHAIN_FILE="generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release

build:
	cmake --build build/Release

.PHONY: conan cmake build
