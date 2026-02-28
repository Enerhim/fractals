cmake_minimum_required(VERSION 4.0)
project(mandelbrot VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES src/*.cpp)
add_executable(mandelbrot ${SRC_FILES} external/glad/src/glad.c)

target_include_directories(mandelbrot PRIVATE include external/glad/include)

add_subdirectory(external/glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(mandelbrot PRIVATE GL glfw)

# Put executable into /bin
set_target_properties(mandelbrot PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                      ${CMAKE_BINARY_DIR}/bin)

# Copy Shaders next to executable bin/shaders
add_custom_command(
  TARGET mandelbrot
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders
          $<TARGET_FILE_DIR:mandelbrot>/shaders)
