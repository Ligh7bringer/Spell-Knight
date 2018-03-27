cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(UNIX)
  message("hello linux!")
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml")
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)
## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths" SYSTEM INTERFACE ${SFML_INCS})
## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_tile_level_loader/*.cpp engine/lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)
## ECM lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_ecm/*.cpp engine/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)
## Texture manager
file(GLOB_RECURSE SOURCE_FILES engine/lib_texture_manager/*.cpp engine/lib_texture_manager/*.h)
add_library(lib_texture_manager STATIC ${SOURCE_FILES})
target_include_directories(lib_texture_manager INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_texture_manager" )
target_link_libraries(lib_texture_manager lib_maths sfml-graphics)
## Input Manager
file(GLOB_RECURSE SOURCE_FILES engine/lib_input_manager/*.cpp engine/lib_input_manager/*.h)
add_library(lib_input_manager STATIC ${SOURCE_FILES})
target_include_directories(lib_input_manager INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_input_manager" )
target_link_libraries(lib_input_manager lib_maths)
## Settings parser
file(GLOB_RECURSE SOURCE_FILES engine/lib_settings_parser/*.cpp engine/lib_settings_parser/*.h)
add_library(lib_settings_parser STATIC ${SOURCE_FILES})
target_include_directories(lib_settings_parser INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_settings_parser" )
target_link_libraries(lib_settings_parser lib_maths)

## Coursework
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
file(GLOB_RECURSE CMPNTS src/components/*.cpp src/components/*.h)
file(GLOB_RECURSE SCENES src/scenes/*.cpp src/scenes/*.h)
add_executable(Coursework ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(PRACTICAL_6_PLATFORMER SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(Coursework lib_engine lib_texture_manager lib_input_manager lib_settings_parser) 
set(EXECUTABLES ${EXECUTABLES} Coursework)

#### Target for copying resources to build dir####
#### put res folder in the correct location based on OS and/or compiler ####
if(UNIX)
  message("Detected Linux! Copying resources to bin/build/...")
   add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
elseif(MSVC)
    message("Detected MSCV! Copying resources....")
    add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
else()
  message("Not Linux or MSVC! Copying resources...")
  add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
endif()

#### Link Dependencies ####
foreach (exe ${EXECUTABLES})
  #Set working directory to build dir
  set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
  )

  target_link_libraries(${exe}
    lib_maths
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-audio debug sfml-audio-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    optimized sfml-graphics debug sfml-graphics-d
    #optimized sfml-main
  )

  #target_link_libraries(${exe} "${CMAKE_SOURCE_DIR}/lib/sfml/extlibs/libs-osx/Frameworks/f‌​reetype.framework/Ve‌​rsions/A/freetype")

  add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()
