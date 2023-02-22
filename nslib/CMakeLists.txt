cmake_minimum_required (VERSION 3.13.5)

file(GLOB_RECURSE HEADERS "*.h")

add_library (nslib SHARED flags.c player.c game.c ${HEADERS})

target_include_directories (nslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(nslib ${liblua_LIBRARY})

