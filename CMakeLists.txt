cmake_minimum_required(VERSION 2.9 FATAL_ERROR)

project(gears)

# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html
find_package(Geant4 10.0 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE}) # auto configure includes & flags

# enable GDML if XercesC_INCLUDE_DIR is defined by Geant4
if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

add_executable(gears gears.cc)
target_link_libraries(gears ${Geant4_LIBRARIES})
# put executable in the source directory where gears.sh locates
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
  add_custom_target(setup ALL echo
    COMMAND echo To install, please add the following line:
    COMMAND echo `tput bold` source ${CMAKE_CURRENT_SOURCE_DIR}/gears.sh`tput sgr0`
    COMMAND echo to `tput bold`~/.bashrc`tput sgr0` in Linux or `tput bold`~/.bash_profile`tput sgr0` in a Mac
    COMMAND echo or `tput bold`~/.zshrc`tput sgr0` if you use zsh instead of bash
    COMMAND echo)
endif()
