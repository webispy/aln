# SPDX-License-Identifier: Apache-2.0

add_executable(aln main.c)
target_link_libraries(aln PUBLIC libaln)
target_include_directories(aln PRIVATE ${glib_INCLUDE_DIRS})

install(TARGETS aln RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES aln.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
