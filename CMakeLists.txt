cmake_minimum_required(VERSION 3.10.0)
project(tinyraytracer VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wshadow
)

# target_compile_options(${PROJECT_NAME} PRIVATE -Werror)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:-g>
  $<$<CONFIG:Debug>:-ggdb>
  $<$<CONFIG:Release>:-O2>
  $<$<CONFIG:Release>:-DNDEBUG>
)
