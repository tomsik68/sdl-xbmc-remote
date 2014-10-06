project(SDL_xbmc_remote)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

find_package (SDL 1.2 REQUIRED)

set (INCLUDE_DIRS ${SDL_INCLUDE_DIR})

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(LIBRARIES ${SDL_LIBRARY})
# if there's possibility to add SDLMain, do it...
if(SDLMAIN_LIBRARY)
    set(LIBRARIES ${LIBRARIES} ${SDLMAIN_LIBRARY})
endif(SDLMAIN_LIBRARY)

target_link_libraries( ${PROJECT_NAME} ${LIBRARIES})
