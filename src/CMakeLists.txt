# SPDX-License-Identifier: Apache-2.0

add_library(libaln SHARED aln.c)

if (NOT MSVC)
    target_compile_options(libaln PRIVATE -fvisibility=hidden)
endif()

target_include_directories(libaln PRIVATE include ${glib_INCLUDE_DIRS})
target_compile_definitions(libaln PRIVATE -DALN_LIBRARY_BUILD)
target_link_libraries(libaln PUBLIC ${glib_LIBRARIES})
target_link_directories(libaln PUBLIC ${glib_LIBRARY_DIRS})

set_target_properties(libaln
	PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR} OUTPUT_NAME aln)

install(TARGETS libaln LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
