cmake_minimum_required(VERSION 3.20)

project(Kaleidoscope LANGUAGES CXX)

# Ensuring C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default build type if not specified
#if(NOT EXISTS CMAKE_BUILD_TYPE )
#  message(STATUS Build type:${CMAKE_BUILD_TYPE})
#  message(STATUS Setting build type as debug)
#  set(CMAKE_BUILD_TYPE "Debug")
#endif()


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Extra scripts
include("cmake/StandardProjectSettings.cmake")
include("cmake/PreventInSourceBuilds.cmake")
include("cmake/CompilerWarnings.cmake")
include("cmake/Sanitizers.cmake")


# Grouping manually enabled options
add_library(additional_options INTERFACE)
target_compile_features(additional_options INTERFACE cxx_std_17)
enable_sanitizers(additional_options)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(ENABLE_PCH "Enable Precompiled Headers" ON)
#if(ENABLE_PCH)
#
#  target_precompile_headers(
#    additional_options
#    INTERFACE
#    <vector>
#    <string>
#    <map>
#    <utility>
#    <algorithm>
#    <wx/wx.h>
#)
#endif()

# Main target setup
include_directories("include")

file(GLOB sources "src/*.cpp")
file(GLOB includes "include/*.hpp" "include/*.h")

add_executable(${PROJECT_NAME} WIN32 ${sources} ${includes})

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME} PRIVATE additional_options)


set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/wxWidgets)
find_package(wxWidgets REQUIRED COMPONENTS net core base)

include(${wxWidgets_USE_FILE})

target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})


# Visual Studio stuff
set_property(TARGET ${PROJECT_NAME} PROPERTY 
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})





