cmake_minimum_required(VERSION 3.16) # CMake quits without it

project(gears) # project name

# http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/InstallationGuide/html/buildtools.html
find_package(Geant4 11.0 REQUIRED ui_all vis_all) # search for Geant4Config.cmake
include(${Geant4_USE_FILE}) # auto configure includes & flags

if(WIN32) # set config type for multi-configuration generators, e.g. Visual Studio, Xcode
  set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING "Release;Debug;..." FORCE)
else() # set default build type for single-configuration generators, e.g. Makefile
  if(NOT CMAKE_BUILD_TYPE) # if not defined by the user
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Release;Debug;..." FORCE)
  endif()
endif() # executable of Release type is leaner & faster than that of Debug type

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) # if not defined by the user
  set(CMAKE_INSTALL_PREFIX "${Geant4_DIR}/../../.." CACHE PATH "Installation prefix" FORCE)
endif() # set default installation prefix

# enable GDML if XercesC_INCLUDE_DIR is defined by Geant4
if(XercesC_INCLUDE_DIR)
  add_definitions(-DhasGDML)
endif()

if(APPLE) # https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
  set(CMAKE_INSTALL_RPATH "${Geant4_DIR}/../..")
endif()  # set RPATH in executable on Mac (must be before add_executable(...))

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cc)
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES})
install(TARGETS ${PROJECT_NAME}) # enable cmake --install
