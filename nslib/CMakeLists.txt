cmake_minimum_required (VERSION 3.13.5)

file(GLOB_RECURSE HEADERS "*.h")

add_library (nslib SHARED flags.c player.c game.c ${HEADERS})

if ("${COMPILER_ID}" STREQUAL "TINYCC")
	execute_process(COMMAND bash -c "dirname ${CMAKE_C_COMPILER}" OUTPUT_VARIABLE CMAKE_C_COMPILER_DIR)
	string(STRIP ${CMAKE_C_COMPILER_DIR} CMAKE_C_COMPILER_DIR)
	set(EXTRA_INCLUDES "${CMAKE_C_COMPILER_DIR}/include")
else()
	set(EXTRA_INCLUDES "")	
endif()

target_include_directories (nslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${EXTRA_INCLUDES})

target_link_libraries(nslib ${liblua_LIBRARY})

set_target_properties(nslib PROPERTIES PREFIX "")
set_target_properties(nslib PROPERTIES OUTPUT_NAME "nslib")

if (NOT "${COMPILER_ID}" STREQUAL "MSVC")
	add_link_options("-Wall")
endif()
