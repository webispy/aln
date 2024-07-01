# SPDX-License-Identifier: Apache-2.0

add_executable(test_default test_default.c)
target_link_libraries(test_default PUBLIC libaln)
target_include_directories(test_default PRIVATE ${glib_INCLUDE_DIRS})

add_test(NAME test_default COMMAND test_default)
