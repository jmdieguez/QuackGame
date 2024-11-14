add_library(ui_lib INTERFACE)

set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_MIXER YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)

# Specify the include directories for this library
target_include_directories(ui_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui_lib INTERFACE ${SDL2_LIBRARIES} SDL2pp::SDL2pp ${SDL2_LIBRARIES})
