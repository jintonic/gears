cmake_minimum_required(VERSION 3.16) # CMake quits without it

project(gears) # project name

set(Geant4_CONFIG_DEBUG TRUE) # let the next command print more information
# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html
find_package(Geant4 11.0 REQUIRED ui_all vis_all) # search for Geant4Config.cmake
include(${Geant4_USE_FILE}) # auto configure includes & flags

# enable GDML if XercesC_INCLUDE_DIR is defined by Geant4
if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

# set RPATH in installed executable on Mac (must be set before the next command)
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
set(CMAKE_INSTALL_RPATH "${Geant4_INCLUDE_DIRS}/../../lib")
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cc)
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})

if(WIN32)
  # remove Debug and other unnecessary configurations
  # https://cmake.org/pipermail/cmake/2007-March/013081.html
  set(CMAKE_CONFIGURATION_TYPES "Release" CACHE INTERNAL "")
  # https://stackoverflow.com/a/37994396/1801749
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
  # automacially add current folder to user PATH environment variable
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cmd /c ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.bat)
  # put executable in build/.. instead of build/
  # https://stackoverflow.com/a/9994922/1801749
  set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
else()
  # put executable in build/.. instead of build/
  # https://stackoverflow.com/a/9994922/1801749
  set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
  # enable make install
  install(TARGETS ${PROJECT_NAME})
endif()

