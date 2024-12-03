cmake_minimum_required(VERSION 3.13)

add_compile_options(-Wno-unused-parameter)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_POSIX_C_SOURCE=200112L")  # Habilita POSIX

project(taller_tp
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
)

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)


if(DEFINED ENV{GLOBAL_INSTALL} AND "$ENV{GLOBAL_INSTALL}" STREQUAL "true")
    message(STATUS "Compilando para instalación global.")
    add_compile_definitions(GLOBAL_INSTALL)
else()
    message(STATUS "Compilando para uso local.")
endif()

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
add_library(quack_game_common STATIC)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)

# Add the source files that make the lib
add_subdirectory(common/)

# Set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(quack_game_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Set the include directories for the library
target_include_directories(quack_game_common PUBLIC .)

# Install libSDL2pp (for client or editor)
if(TALLER_CLIENT OR TALLER_EDITOR)
    add_subdirectory(ui/)
    # find_package(SDL2 REQUIRED)
    # find_package(SDL2_image REQUIRED)
    target_include_directories(quack_game_common PUBLIC ${SDL2_INCLUDE_DIRS})
endif()

# Program section
if(TALLER_CLIENT)
    find_package(Qt5 COMPONENTS
            Core
            Widgets
            Multimedia
            REQUIRED
    )

    # Activar las opciones automáticas de Qt
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)


    add_executable(quack_game_client ${UIS_HEADERS})

    # Configurar dependencias y subdirectorios
    add_dependencies(quack_game_client quack_game_common SDL2pp::SDL2pp)
    add_subdirectory(client)
    set_project_warnings(quack_game_client ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Enlazar las bibliotecas necesarias
    set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/client/view")
    qt5_wrap_ui(UIS_HEADERS
            ./view/mainwindow.ui
    )
    target_link_libraries(quack_game_client
            quack_game_common
            yaml-cpp::yaml-cpp
            ui_lib
            Qt5::Core
            Qt5::Widgets
            Qt5::Multimedia
    )
endif()

if(TALLER_SERVER)
    add_executable(quack_game_server)

    # Make them depend on quack_game_common lib
    add_dependencies(quack_game_server quack_game_common)

    # Add source files and enable warnings
    add_subdirectory(server)
    set_project_warnings(quack_game_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the quack_game_common lib target
    target_link_libraries(quack_game_server quack_game_common yaml-cpp::yaml-cpp)
endif()

if(TALLER_EDITOR)
    add_executable(quack_game_editor)

    # Make them depend on quack_game_common lib
    add_dependencies(quack_game_editor quack_game_common SDL2pp::SDL2pp)

    # Add source files and enable warnings
    add_subdirectory(editor)
    set_project_warnings(quack_game_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link with SDL2 and its modules
    target_link_libraries(quack_game_editor
        quack_game_common
        # SDL2::SDL2
        # SDL2_image::SDL2_image
        yaml-cpp::yaml-cpp
        ui_lib
    )
endif()

# Testing section
if(TALLER_TESTS)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(quack_game_tests  tests/testProtocolServer.cpp server/protocol.cpp)
    add_dependencies(quack_game_tests quack_game_common)
    target_include_directories(quack_game_tests PUBLIC .)
    add_subdirectory(tests/)
    set_project_warnings(quack_game_tests ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

    target_include_directories(quack_game_tests
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
    )

    target_link_libraries(quack_game_tests
        quack_game_common
        GTest::gtest_main
        GTest::gmock
    )
endif()