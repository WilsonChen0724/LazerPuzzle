# CMakeLists.txt for SDL_bgi 
# GG, 2023-03-23

# --- Building, thanks to cmake

cmake_minimum_required (VERSION 3.5.0)

set (SDL_BGI_VERSION 3.0.2)

# Project name
project (SDL_bgi VERSION ${SDL_BGI_VERSION} LANGUAGES C)

# Strip the library after building
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")

# Include SDL2 support for cmake
find_package (SDL2 REQUIRED)
# fix provided by Austin Hurst
include_directories (SDL_bgi ${SDL2_INCLUDE_DIRS})

# Default install directory variables
include (GNUInstallDirs)

# Find source files
file (GLOB SOURCES src/SDL_bgi.c)

# Include header files
include_directories (src)

# Create shared library
add_library (${PROJECT_NAME} SHARED ${SOURCES})
# fix provided by Austin Hurst
target_link_libraries (SDL_bgi ${SDL2_LIBRARIES})

# Install library
install (TARGETS ${PROJECT_NAME} 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # Windows
)

# Install library headers
file (GLOB HEADERS src/graphics.h)
install (FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
file (GLOB HEADERS src/SDL_bgi.h)
install (FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SDL2/)

# Install Python support?
# find_package (Python3 COMPONENTS Interpreter Development)
# file (GLOB python_kb src/sdl_bgi.py)
# install (FILES ${python_kb} DESTINATION ${Python3_STDLIB})

# Install documentation files
install (FILES AUTHORS BUGS ChangeLog INSTALL_GNU-Linux.md INSTALL_macOS.md
  INSTALL_Windows.md LICENSE README.md sdl_bgi.spec TODO VERSION
  DESTINATION ${CMAKE_INSTALL_DOCDIR})

# Install documentation directory
file (GLOB docs doc/*)
install (FILES ${docs} DESTINATION ${CMAKE_INSTALL_DOCDIR}/doc)

# Install man page
file (GLOB man doc/graphics.3.gz)
install (FILES ${man} DESTINATION ${CMAKE_INSTALL_MANDIR}/man3)

# Install test and demo programs
install (DIRECTORY test/ DESTINATION ${CMAKE_INSTALL_DOCDIR}/test)
install (DIRECTORY demo/ DESTINATION ${CMAKE_INSTALL_DOCDIR}/demo)

# --- Packaging, thanks to cpack

if (EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
include (InstallRequiredSystemLibraries)

if (WIN32)
  set (CPACK_GENERATOR "ZIP")
else ()
  set (CPACK_GENERATOR "RPM;DEB")
endif()

set (CPACK_PACKAGE_VERSION ${SDL_BGI_VERSION})
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CONTACT "guido.gonzato@gmail.com")

# DEB (Debian, Ubuntu, Mint) package
set (CPACK_DEBIAN_PACKAGE_NAME "sdl_bgi")
set (CPACK_DEBIAN_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION})
set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCH_DEB})
set (CPACK_DEBIAN_PACKAGE_MAINTAINER ${CONTACT})
set (CPACK_DEBIAN_PACKAGE_DESCRIPTION "SDL2-based 'GRAPHICS.H' implementation")
set (CPACK_DEBIAN_PACKAGE_SECTION "libs")
set (CPACK_DEBIAN_COMPRESSION_TYPE "gzip")
set (CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-dev (>= 2.0.0)")

# RPM (Fedora) package
set (CPACK_RPM_PACKAGE_SUMMARY "SDL2-based 'GRAPHICS.H' implementation")
set (CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
set (CPACK_PACKAGE_VERSION  ${CPACK_PACKAGE_VERSION})
set (CPACK_PACKAGE_ARCHITECTURE ${ARCH_RPM})
set (CPACK_RPM_PACKAGE_RELEASE "1")
set (CPACK_RPM_PACKAGE_LICENSE "zlib")
set (CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set (CPACK_RPM_PACKAGE_VENDOR "GG")
set (CPACK_RPM_PACKAGE_DESCRIPTION "SDL_bgi is a Borland Graphics Interface ('GRAPHICS.H') implementation based on SDL2. This library strictly emulates BGI functions, making it possible to compile SDL2 versions of programs written for Turbo C/Borland C++. ARGB colours, vector fonts, mouse support, and multiple
windows are also implemented; further, native SDL2 functions may be used in SDL_bgi programs.")
set (CPACK_RPM_PACKAGE_REQUIRES "SDL2-devel >= 2.0.0")
set (CPACK_PACKAGE_CONTACT ${CONTACT})

set (CPACK_COMPONENTS_ALL Libraries ApplicationData)

include (CPack)

endif (EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

# End of file CMakeLists.txt
