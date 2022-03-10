cmake_minimum_required(VERSION 3.4)

project(wordKit VERSION 0.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

# set library cpp
set(SOURCES src/Document.cpp
            src/Element.cpp
            src/Paragraph.cpp
            src/Run.cpp
            src/Table.cpp
        src/SectionProperty.cpp src/SectionProperty.h)
# set library headers
file(GLOB HEADERS src/*.h
                  src/*.hpp)

add_library(wordKit STATIC ${SOURCES} ${HEADERS})

add_subdirectory(libs/pugixml)
add_subdirectory(libs/zip)

target_link_libraries(wordKit PUBLIC pugixml)
target_link_libraries(wordKit PUBLIC zip)

target_include_directories(wordKit PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libs/pugixml"
                          "${PROJECT_SOURCE_DIR}/libs/zip"
                          )
                          
# add sample
add_executable(sample src/Sample.cpp)
target_link_libraries(sample PUBLIC wordKit)


