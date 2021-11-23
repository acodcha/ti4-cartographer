cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define the C++ and build settings.
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64 -ffast-math -O3 -Wall -Wno-return-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the CMake project.
project("TI4Cartographer" VERSION 1.0.0 LANGUAGES CXX)
option(BUILD_DOCS "Build the documentation using Doxygen." OFF)
option(BUILD_TESTING "Build the tests." ON)

# Build the Cartographer executable.
set(CARTOGRAPHER_EXECUTABLE_NAME "ti4cartographer")
add_executable(${CARTOGRAPHER_EXECUTABLE_NAME} source/Cartographer.cpp)
target_link_libraries(${CARTOGRAPHER_EXECUTABLE_NAME} stdc++fs)

# Build the Atlas executable.
set(ATLAS_EXECUTABLE_NAME "ti4atlas")
add_executable(${ATLAS_EXECUTABLE_NAME} source/Atlas.cpp)
target_link_libraries(${ATLAS_EXECUTABLE_NAME} stdc++fs)

# Install the executables.
install(TARGETS ${CARTOGRAPHER_EXECUTABLE_NAME} DESTINATION /usr/local/bin)
install(TARGETS ${ATLAS_EXECUTABLE_NAME} DESTINATION /usr/local/bin)

# Build the tests.
include(CTest)
if(BUILD_TESTING)
  enable_testing()
  add_test(NAME atlas_test COMMAND ../test/atlas.sh)
  add_test(NAME cartographer_2_players_regular_high COMMAND ../test/2_players_regular_high.sh)
  add_test(NAME cartographer_3_players_regular_moderate COMMAND ../test/3_players_regular_moderate.sh)
  add_test(NAME cartographer_3_players_small_moderate COMMAND ../test/3_players_small_moderate.sh)
  add_test(NAME cartographer_3_players_large_high COMMAND ../test/3_players_large_high.sh)
  add_test(NAME cartographer_4_players_regular_moderate COMMAND ../test/4_players_regular_moderate.sh)
  add_test(NAME cartographer_4_players_large_high COMMAND ../test/4_players_large_high.sh)
  add_test(NAME cartographer_5_players_regular_moderate COMMAND ../test/5_players_regular_moderate.sh)
  add_test(NAME cartographer_5_players_small_moderate COMMAND ../test/5_players_small_moderate.sh)
  add_test(NAME cartographer_5_players_large_high COMMAND ../test/5_players_large_high.sh)
  add_test(NAME cartographer_6_players_regular_moderate COMMAND ../test/6_players_regular_moderate.sh)
  add_test(NAME cartographer_6_players_large_moderate COMMAND ../test/6_players_large_moderate.sh)
  add_test(NAME cartographer_7_players_regular_moderate COMMAND ../test/7_players_regular_moderate.sh)
  add_test(NAME cartographer_7_players_large_high COMMAND ../test/7_players_large_high.sh)
  add_test(NAME cartographer_8_players_regular_moderate COMMAND ../test/8_players_regular_moderate.sh)
  add_test(NAME cartographer_8_players_large_high COMMAND ../test/8_players_large_high.sh)
endif()

# Build the documentation.
if(BUILD_DOCS)
  find_package(Doxygen REQUIRED dot)
  if(NOT Doxygen_FOUND)
    message(WARNING "Cannot build the documentation because Doxygen is not installed. Install it with \"sudo apt install doxygen graphviz texlive texlive-fonts-extra\".")
    return()
  endif()
  add_custom_target(
    docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
    COMMENT "Building the documentation using Doxygen..."
    VERBATIM)
endif()
