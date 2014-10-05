project(SDL_xbmc_remote)
cmake_minimum_required(VERSION 3.0)
aux_source_directory(. SRC_LIST)

find_package (SDL 1.2 REQUIRED)
find_package(OpenGL REQUIRED)

set (INCLUDE_DIRS ${SDL_INCLUDE_DIR})

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries( ${PROJECT_NAME} ${SDL_LIBRARY} ${SDLMAIN_LIBRARY} ${OPENGL_LIBRARIES})
