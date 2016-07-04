cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project( rlib)

include( "../LibCMakeCommon.cmake")
set( BUILD_SHARED_LIBS TRUE)

set( SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
include_directories( "${INCLUDE_DIR}")

# Include the build directory because generated header files sit here.
include_directories( "${PROJECT_BINARY_DIR}")

# Eigen3
find_package( Eigen3 3.1.2 REQUIRED)
include_directories( ${EIGEN3_INCLUDE_DIR})

# Boost
find_package( Boost 1.58 REQUIRED COMPONENTS system filesystem thread random regex)
include_directories( ${Boost_INCLUDE_DIRS})
message( STATUS "Boost_LIBRARY_DIR=${Boost_LIBRARY_DIR}")
message( STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

set( INCLUDE_FILES
    "${INCLUDE_DIR}/ConvexOptimiser.h"
    "${INCLUDE_DIR}/Convert.h"
    "${INCLUDE_DIR}/template/Convert_template.h"
    "${INCLUDE_DIR}/CmdLine.h"
    "${INCLUDE_DIR}/CpuTimer.h"
    "${INCLUDE_DIR}/Exceptions.h"
    "${INCLUDE_DIR}/FileIO.h"
    "${INCLUDE_DIR}/LinearRegressor.h"
    #"${INCLUDE_DIR}/Lock.h"
    "${INCLUDE_DIR}/NewtonRaphson.h"
    "${INCLUDE_DIR}/Pack.h"
    "${INCLUDE_DIR}/ProgressDelegate.h"
    "${INCLUDE_DIR}/ProgressUpdater.h"
    "${INCLUDE_DIR}/Random.h"
    "${INCLUDE_DIR}/SymmetricBitSet.h"
    "${INCLUDE_DIR}/SymmetricMatrix.h"
    "${INCLUDE_DIR}/template/SymmetricMatrix_template.h"
    #"${INCLUDE_DIR}/ThreadManager.h"
    "${INCLUDE_DIR}/Timer.h"
    "${INCLUDE_DIR}/rlib.h"
    "${INCLUDE_DIR}/ustring.h"
    "${INCLUDE_DIR}/UndoStack.h"
    "${INCLUDE_DIR}/template/UndoStack_template.h"
    "${INCLUDE_DIR}/Vectors.h")

set( SRC_FILES
    #${SRC_DIR}/BmpImage
    #${SRC_DIR}/Compression
    ${SRC_DIR}/ConvexOptimiser
    ${SRC_DIR}/Convert
    ${SRC_DIR}/CmdLine
    ${SRC_DIR}/CpuTimer
    ${SRC_DIR}/Exceptions
    #${SRC_DIR}/CubeRObj
    ${SRC_DIR}/FileIO
    #${SRC_DIR}/HttpClient  # Uses cURL lib
    #${SRC_DIR}/HTTPClient
    #${SRC_DIR}/ImageHandling
    ${SRC_DIR}/LinearRegressor
    #${SRC_DIR}/Lock
    #${SRC_DIR}/Model
    ${SRC_DIR}/NewtonRaphson
    ${SRC_DIR}/Pack
    #${SRC_DIR}/ParseXFile
    ${SRC_DIR}/ProgressDelegate
    ${SRC_DIR}/ProgressUpdater
    ${SRC_DIR}/Random
    #${SRC_DIR}/Scene
    #${SRC_DIR}/SdlTimer
    ${SRC_DIR}/SymmetricBitSet
    #${SRC_DIR}/TCPClient
    #${SRC_DIR}/ThreadManager
    ${SRC_DIR}/Timer
    ${SRC_DIR}/ustring
    #${SRC_DIR}/Vec2d   # Use eigen instead!
    #${SRC_DIR}/Vec     # Use eigen instead!
    ${SRC_DIR}/Vectors
    )

# Require generate_export_header for .lib import libraries associated with Windows DLLs (if BUILD_SHARED_LIBS is true)
include(GenerateExportHeader)
add_library( ${PROJECT_NAME} ${SRC_FILES} ${INCLUDE_FILES})
generate_export_header( ${PROJECT_NAME}
    BASE_NAME ${PROJECT_NAME}
    EXPORT_MACRO_NAME ${PROJECT_NAME}_EXPORT
    EXPORT_FILE_NAME ${PROJECT_NAME}_Export.h
    STATIC_DEFINE ${PROJECT_NAME}_BUILT_AS_STATIC)

target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES})

set( CMAKE_INSTALL_PREFIX "${LOCALLIBS}/${PROJECT_NAME}")
install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin"
                                 LIBRARY DESTINATION "lib"
                                 ARCHIVE DESTINATION "lib/static")

install( FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_Export.h" DESTINATION "include")
install( FILES ${INCLUDE_FILES} DESTINATION "include")
install( DIRECTORY "${INCLUDE_DIR}/template" DESTINATION "include")
# Copy across this library's Find cmake module to ${LOCALLIBS}/cmake
install( FILES "${PROJECT_SOURCE_DIR}/../CMakeModules/FindRLIB.cmake" DESTINATION "${LOCALLIBS}/cmake")

