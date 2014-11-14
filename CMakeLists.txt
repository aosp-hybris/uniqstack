PROJECT(copycat)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

# Set version
SET(COPYCAT_VERSION_MAJOR "0")
SET(COPYCAT_VERSION_MINOR "1")
SET(COPYCAT_VERSION_PATCH "0")
SET(COPYCAT_VERSION "${COPYCAT_VERSION_MAJOR}.${COPYCAT_VERSION_MINOR}.${COPYCAT_VERSION_PATCH}")

# Find includes in corresponding build directories and add support for qt
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

# We need to use CXX11 to build this application
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
IF (NOT COMPILER_SUPPORTS_CXX11)
    MESSAGE(FATAL_ERROR "You need C++11 supported!!")
ENDIF()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -std=c++11")

# Installation directories
INCLUDE(GNUInstallDirs)

# Find required libraries
FIND_PACKAGE(Qt5Gui REQUIRED)
IF(NOT Qt5Gui_FOUND)
    MESSAGE(FATAL_ERROR "Qt5Gui module is required!")
ENDIF()

FIND_PACKAGE(Qt5Qml REQUIRED)
IF(NOT Qt5Qml_FOUND)
  MESSAGE(FATAL_ERROR "Qt5Qml module is required!")
ENDIF()

FIND_PACKAGE(Qt5Quick REQUIRED)
IF(NOT Qt5Quick_FOUND)
  MESSAGE(FATAL_ERROR "Qt5Quick module is required!")
ENDIF()

FIND_PACKAGE(Qt5Compositor REQUIRED)
IF(NOT Qt5Compositor_FOUND)
  MESSAGE(FATAL_ERROR "Qt5Compositor module is required!")
ENDIF()

FIND_PACKAGE(Qt5DBus REQUIRED)
IF(NOT Qt5DBus_FOUND)
  MESSAGE(FATAL_ERROR "Qt5DBus module is required!")
ENDIF()

# Add source dirs
ADD_SUBDIRECTORY(src)
