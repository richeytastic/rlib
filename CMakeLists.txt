cmake_minimum_required(VERSION 3.12.2 FATAL_ERROR)

project( rlib)

set( WITH_BOOST TRUE)
set( WITH_EIGEN TRUE)
include( "cmake/FindLibs.cmake")

set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set( SRC_DIR "${PROJECT_SOURCE_DIR}/src")
include_directories( ${INCLUDE_DIR})

set( INCLUDE_FILES
    "${INCLUDE_DIR}/${PROJECT_NAME}.h"
    "${INCLUDE_DIR}/ConvexOptimiser.h"
    "${INCLUDE_DIR}/Convert.h"
    "${INCLUDE_DIR}/template/Convert_template.h"
    "${INCLUDE_DIR}/CmdLnArgsParser.h"
    "${INCLUDE_DIR}/template/CmdLnArgsParser_template.h"
    "${INCLUDE_DIR}/CpuTimer.h"
    "${INCLUDE_DIR}/Exceptions.h"
    "${INCLUDE_DIR}/FileIO.h"
    "${INCLUDE_DIR}/IOFormats.h"
    "${INCLUDE_DIR}/LinearRegressor.h"
    #"${INCLUDE_DIR}/Lock.h"
    "${INCLUDE_DIR}/MathUtil.h"
    "${INCLUDE_DIR}/NewtonRaphson.h"
    "${INCLUDE_DIR}/Pack.h"
    "${INCLUDE_DIR}/ProgressDelegate.h"
    "${INCLUDE_DIR}/ProgressUpdater.h"
    "${INCLUDE_DIR}/Random.h"
    "${INCLUDE_DIR}/RangedScalarDistribution.h"
    "${INCLUDE_DIR}/Round.h"
    "${INCLUDE_DIR}/SymmetricBitSet.h"
    "${INCLUDE_DIR}/SymmetricMatrix.h"
    "${INCLUDE_DIR}/template/SymmetricMatrix_template.h"
    #"${INCLUDE_DIR}/ThreadManager.h"
    "${INCLUDE_DIR}/Timer.h"
    "${INCLUDE_DIR}/ustring.h"
    "${INCLUDE_DIR}/Vectors.h")

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
    ${SRC_DIR}/IOFormats
    #${SRC_DIR}/HttpClient  # Uses cURL lib
    #${SRC_DIR}/HTTPClient
    #${SRC_DIR}/ImageHandling
    ${SRC_DIR}/LinearRegressor
    #${SRC_DIR}/Lock
    ${SRC_DIR}/MathUtil
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
