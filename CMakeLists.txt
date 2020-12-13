cmake_minimum_required(VERSION 2.9 FATAL_ERROR)

project(gears)

# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html#cmake-build-system-geant4config-cmake
find_package(Geant4 10.0 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

add_executable(gears gears.cc)
target_link_libraries(gears ${Geant4_LIBRARIES})

# remove Debug and other unnecessary configurations
# https://cmake.org/pipermail/cmake/2007-March/013081.html
set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING INTERNAL FORCE)

if(WIN32)
    add_custom_command(TARGET gears POST_BUILD COMMAND powershell.exe Release/gears.bat)
    # https://stackoverflow.com/a/37994396/1801749
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT gears)
    configure_file(install/gears.bat Release/gears.bat COPYONLY)
endif()