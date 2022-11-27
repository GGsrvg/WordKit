cmake_minimum_required(VERSION 3.14)

project(
    WordKit 
    VERSION 0.2.0
    DESCRIPTION "C++ library for generate docx documents"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(WORDKIT_BUILD_TESTS "Build WORDKIT tests" OFF)
option(WORDKIT_BUILD_EXAMPLES "Build WORDKIT examples" OFF)
option(WORDKIT_BUILD_DOCS "Build WORDKIT documentation" OFF)
option(WORDKIT_INSTALL "Generate target for installing WORDKIT" ${is_top_level})
set_if_undefined(WORDKIT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/WORDKIT" CACHE STRING
    "Install path for WORDKIT package-related CMake files")

if(DEFINED WORDKIT_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${WORDKIT_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(WordKit)
add_library(WordKit::WordKit ALIAS WordKit)

#----------------------------------------------------------------------------------------------------------------------
# dependencies
#----------------------------------------------------------------------------------------------------------------------

# Search for your dependencies here

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(WordKit EXPORT_FILE_NAME include/WordKit/${export_file_name})

set(sources
    include/WordKit/Document.h
    include/WordKit/Element.h
    include/WordKit/export.h
    include/WordKit/Paragraph.h
    include/WordKit/Run.h
    include/WordKit/SectionProperty.h
    include/WordKit/Table.h
    src/Document.cpp
    src/Element.cpp
    src/Paragraph.cpp
    src/Run.cpp
    src/SectionProperty.cpp
    src/Table.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(WordKit PRIVATE ${sources})
target_compile_definitions(WordKit PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:WORDKIT_STATIC_DEFINE>")

target_include_directories(WordKit
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(WordKit PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(WORDKIT_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/wordkit-config.cmake.in WordKit-config.cmake
        INSTALL_DESTINATION "${WORDKIT_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(WordKit-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS WordKit EXPORT WordKit_export
        RUNTIME COMPONENT WordKit
        LIBRARY COMPONENT WordKit NAMELINK_COMPONENT WordKit-dev
        ARCHIVE COMPONENT WordKit-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT WordKit-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/WordKit/${export_file_name}"
        COMPONENT WordKit-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/WordKit")

    set(targets_file "WordKit-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "WordKit-static-targets.cmake")
    endif()

    install(EXPORT WordKit_export
        COMPONENT WordKit-dev
        FILE "${targets_file}"
        DESTINATION "${WORDKIT_INSTALL_CMAKEDIR}"
        NAMESPACE WordKit::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/WordKit-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/WordKit-config-version.cmake"
        COMPONENT WordKit-dev
        DESTINATION "${WORDKIT_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:WordKit>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:WordKit>/$<TARGET_FILE_PREFIX:WordKit>$<TARGET_FILE_BASE_NAME:WordKit>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT WordKit-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

# if(WORDKIT_BUILD_TESTING)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# if(WORDKIT_BUILD_EXAMPLES)
#     add_subdirectory(examples)
# endif()

# if(WORDKIT_BUILD_DOCS)
#     find_package(Doxygen REQUIRED)
#     doxygen_add_docs(docs include)
# endif()
