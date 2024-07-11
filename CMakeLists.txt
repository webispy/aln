# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.9)
project(aln)

include(GNUInstallDirs)
include(FindPkgConfig)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ standard: c++11 (not gnu++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# C standard: gnu99 (not c99)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)

# version: 0.1.1
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

pkg_check_modules(glib REQUIRED glib-2.0)

# Global include directories
include_directories(include)

# Public header files
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aln/)

# pkg-config file
if(NOT DEFINED CMAKE_LIBRARY_ARCHITECTURE)
    set(libdir "\${prefix}/lib")
else()
    set(libdir "\${prefix}/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
endif()
set(includedir "\${prefix}/include/aln")
configure_file(aln.pc.in ${PROJECT_BINARY_DIR}/aln.pc @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/aln.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)

if (NOT MSVC)
    add_compile_options(-g -Werror -Wall)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tool)
add_subdirectory(tests)
