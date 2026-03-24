cmake_minimum_required(VERSION 4.1)

set(CMAKE_C_COMPILER "/opt/homebrew/Cellar/llvm/22.1.1/bin/clang")
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME wolf3d)
project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

set(CMAKE_BUILD_TYPE Debug CACHE STRING "")

set(ASAN "0" CACHE STRING "")
if(NOT ASAN STREQUAL "0")
  add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
  add_link_options(-fsanitize=address -fno-omit-frame-pointer -g)
endif()
unset(ASAN)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
set(DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")

#add_compile_options(-O3)
#add_link_options(-O3)
add_compile_definitions(PROJECT_PATH="${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES "srcs/*.c")
# set(SOURCES srcs/main.c)
# list(TRANSFORM SOURCES PREPEND "srcs/")
# list(TRANSFORM SOURCES APPEND ".c")

add_executable(${PROJECT_NAME} ${SOURCES})

# -flto=thin -O3
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_include_directories(${PROJECT_NAME} PRIVATE includes)
target_include_directories(${PROJECT_NAME} PRIVATE libft/includes)
target_include_directories(${PROJECT_NAME} PRIVATE libtpool/includes)
target_include_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/include/)

target_link_directories(${PROJECT_NAME} PRIVATE libft)
target_link_directories(${PROJECT_NAME} PRIVATE libtpool)
target_link_directories(${PROJECT_NAME} PRIVATE /opt/homebrew/lib/)

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL2 SDL2_image SDL2_ttf SDL2_mixer tpool ft pthread m
)


# copy shaders to build dir
# add_custom_command(
#   TARGET ${PROJECT_NAME} POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader/)

