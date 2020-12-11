cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(gears)

# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html#cmake-build-system-geant4config-cmake
find_package(Geant4 10.0 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

add_executable(gears gears.cc)
target_link_libraries(gears ${Geant4_LIBRARIES})
