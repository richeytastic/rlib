# =============================================================================
# The rlib CMake configuration file.
#
#           ** File generated automatically, DO NOT MODIFY! ***

# To use from an external project, in your project's CMakeLists.txt add:
#   FIND_PACKAGE( rlib REQUIRED)
#   INCLUDE_DIRECTORIES( rlib ${rlib_INCLUDE_DIRS})
#   LINK_DIRECTORIES( ${rlib_LIBRARY_DIR})
#   TARGET_LINK_LIBRARIES( MY_TARGET_NAME ${rlib_LIBRARIES})
#
# This module defines the following variables:
#   - rlib_FOUND         : True if rlib is found.
#   - rlib_ROOT_DIR      : The root directory where rlib is installed.
#   - rlib_INCLUDE_DIRS  : The rlib include directories.
#   - rlib_LIBRARY_DIR   : The rlib library directory.
#   - rlib_LIBRARIES     : The rlib imported libraries to link to.
#
# =============================================================================

get_filename_component( rlib_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component( rlib_ROOT_DIR  "${rlib_CMAKE_DIR}"           PATH)

set( rlib_INCLUDE_DIRS "${rlib_ROOT_DIR}/../include" CACHE PATH "The rlib include directories.")
set( rlib_LIBRARY_DIR  "${rlib_ROOT_DIR}"            CACHE PATH "The rlib library directory.")

include( "${CMAKE_CURRENT_LIST_DIR}/Macros.cmake")
get_library_suffix( _lsuff)
set( _hints rlib${_lsuff} librlib${_lsuff})
find_library( rlib_LIBRARIES NAMES ${_hints} PATHS "${rlib_LIBRARY_DIR}/static" "${rlib_LIBRARY_DIR}")
set( rlib_LIBRARIES     ${rlib_LIBRARIES}         CACHE FILEPATH "The rlib imported libraries to link to.")

# handle QUIETLY and REQUIRED args and set rlib_FOUND to TRUE if all listed variables are TRUE
include( "${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake")
find_package_handle_standard_args( rlib rlib_FOUND rlib_LIBRARIES rlib_INCLUDE_DIRS)
