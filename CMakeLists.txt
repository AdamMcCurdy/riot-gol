cmake_minimum_required(VERSION 3.31)
project(riot_gol)

set(CMAKE_CXX_STANDARD 20)

add_executable(riot_gol main.cpp)

# Install targets
install(TARGETS riot_gol DESTINATION bin)

# Install sample_input.txt
install(FILES "${CMAKE_SOURCE_DIR}/sample_input.txt" DESTINATION bin)

# Add a custom target to create a package with both the executable and sample_input.txt
add_custom_target(package
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/package"
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:riot_gol> "${CMAKE_BINARY_DIR}/package/"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/sample_input.txt" "${CMAKE_BINARY_DIR}/package/"
        COMMAND ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_BINARY_DIR}/riot_gol_$<IF:$<BOOL:${WIN32}>,win,unix>.zip" --format=zip "${CMAKE_BINARY_DIR}/package"
)