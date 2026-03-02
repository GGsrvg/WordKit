cmake_minimum_required(VERSION 3.14)

project(
    WordKit 
    VERSION 0.3.0
    DESCRIPTION "C++ library for generate docx documents"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Add dependencies
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY  https://github.com/zeux/pugixml.git
    GIT_TAG         v1.15
    GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(pugixml)

FetchContent_Declare(
    zip
    GIT_REPOSITORY  https://github.com/kuba--/zip.git
    GIT_TAG         v0.3.6
    GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(zip)

# Add library
file(GLOB_RECURSE
    HEADER_FILES
    "${PROJECT_SOURCE_DIR}/include/WordKit/*.h"
    "${PROJECT_SOURCE_DIR}/include/WordKit/*.hpp")
file(GLOB_RECURSE
    SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(
    WordKit
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(
    WordKit
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(
    WordKit PUBLIC
    pugixml::pugixml
    zip::zip
)

# Add example
add_executable(
    example
    "${PROJECT_SOURCE_DIR}/examples/example.cpp"
)

target_link_libraries(
    example
    PRIVATE WordKit
)

target_compile_options(
    example
    PRIVATE -Wall -Wextra -Wpedantic
)

# Print finished message
message(STATUS "CMake configuration completed successfully!")