cmake_minimum_required(VERSION 3.12.2 FATAL_ERROR)

project( rlib)

set( WITH_BOOST TRUE)
set( WITH_EIGEN TRUE)
include( "cmake/FindLibs.cmake")

set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set( INCLUDE_F "${INCLUDE_DIR}/${PROJECT_NAME}")
set( SRC_DIR "${PROJECT_SOURCE_DIR}/src")
include_directories( ${INCLUDE_DIR})
include_directories( ${INCLUDE_F})

set( INCLUDE_FILES
    "${INCLUDE_F}.h"
    "${INCLUDE_F}/ConvexOptimiser.h"
    "${INCLUDE_F}/Convert.h"
    "${INCLUDE_F}/CmdLnArgsParser.h"
    "${INCLUDE_F}/CpuTimer.h"
    "${INCLUDE_F}/Exceptions.h"
    "${INCLUDE_F}/FileIO.h"
    "${INCLUDE_F}/LinearRegressor.h"
    "${INCLUDE_F}/MathUtil.h"
    "${INCLUDE_F}/Memory.h"
    "${INCLUDE_F}/NewtonRaphson.h"
    "${INCLUDE_F}/Pack.h"
    "${INCLUDE_F}/ProgressDelegate.h"
    "${INCLUDE_F}/ProgressUpdater.h"
    "${INCLUDE_F}/Random.h"
    "${INCLUDE_F}/RangedScalarDistribution.h"
    "${INCLUDE_F}/Round.h"
    "${INCLUDE_F}/SymmetricBitSet.h"
    "${INCLUDE_F}/SymmetricMatrix.h"
    "${INCLUDE_F}/Timer.h"
    "${INCLUDE_F}/ustring.h"
    "${INCLUDE_F}/Vectors.h")

set( SRC_FILES
    #${SRC_DIR}/BmpImage
    #${SRC_DIR}/Compression
    ${SRC_DIR}/ConvexOptimiser
    ${SRC_DIR}/Convert
    ${SRC_DIR}/CmdLnArgsParser
    ${SRC_DIR}/CpuTimer
    ${SRC_DIR}/Exceptions
    #${SRC_DIR}/CubeRObj
    ${SRC_DIR}/FileIO
    #${SRC_DIR}/HttpClient  # Uses cURL lib
    #${SRC_DIR}/HTTPClient
    #${SRC_DIR}/ImageHandling
    ${SRC_DIR}/LinearRegressor
    #${SRC_DIR}/Lock
    ${SRC_DIR}/MathUtil
    ${SRC_DIR}/Memory
    #${SRC_DIR}/Model
    ${SRC_DIR}/NewtonRaphson
    ${SRC_DIR}/Pack
    #${SRC_DIR}/ParseXFile
    ${SRC_DIR}/ProgressDelegate
    ${SRC_DIR}/ProgressUpdater
    ${SRC_DIR}/Random
    ${SRC_DIR}/RangedScalarDistribution
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

add_library( ${PROJECT_NAME} ${SRC_FILES} ${INCLUDE_FILES})

include( "cmake/LinkLibs.cmake")
