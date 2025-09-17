cmake_minimum_required(VERSION 3.16) # CMake quits without it

project(gears)

set(Geant4_CONFIG_DEBUG TRUE) # let the next command print more information
# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html
find_package(Geant4 11.0 REQUIRED ui_all vis_all) # search for Geant4Config.cmake
include(${Geant4_USE_FILE}) # auto configure includes & flags

# enable GDML if XercesC_INCLUDE_DIR is defined by Geant4
if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

# set RPATH in installed gears on Mac (must be set before the next command)
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
set(CMAKE_INSTALL_RPATH "${Geant4_INCLUDE_DIRS}/../../lib")
add_executable(gears gears.cc)
target_link_libraries(gears ${Geant4_LIBRARIES})
# put executable in the source directory where gears.sh and gears.bat locate
# https://stackoverflow.com/a/9994922/1801749
set_target_properties(gears PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# hide CMAKE_INSTALL_PREFIX from novice
mark_as_advanced(FORCE CMAKE_INSTALL_PREFIX X11_xcb_icccm_INCLUDE_PATH
  X11_xcb_icccm_LIB X11_xcb_util_INCLUDE_PATH X11_xcb_util_LIB
  X11_xcb_xfixes_INCLUDE_PATH X11_xcb_xfixes_LIB)

if(WIN32)
  # remove Debug and other unnecessary configurations
  # https://cmake.org/pipermail/cmake/2007-March/013081.html
  set(CMAKE_CONFIGURATION_TYPES "Release" CACHE INTERNAL "")
  # https://stackoverflow.com/a/37994396/1801749
  set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT gears)
  # automacially add \path\to\gears to user PATH environment variable
  add_custom_command(TARGET gears POST_BUILD
    COMMAND cmd /c ${CMAKE_CURRENT_SOURCE_DIR}/gears.bat)
else()
  install(TARGETS gears)
  add_custom_target(setup ALL echo
    COMMAND echo run make install to copy gears executable to a desired folder.
    COMMAND echo)
endif()

