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
    "${INCLUDE_F}/Convert.h"
    "${INCLUDE_F}/ConvexOptimiser.h"
    "${INCLUDE_F}/CpuTimer.h"
    "${INCLUDE_F}/Exceptions.h"
    "${INCLUDE_F}/FileIO.h"
    "${INCLUDE_F}/LinearRegressor.h"
    "${INCLUDE_F}/MathUtil.h"
    "${INCLUDE_F}/Memory.h"
    "${INCLUDE_F}/MultiLock.h"
    "${INCLUDE_F}/NewtonRaphson.h"
    "${INCLUDE_F}/Pack.h"
    "${INCLUDE_F}/Profiling.h"
    "${INCLUDE_F}/ProgressDelegate.h"
    "${INCLUDE_F}/ProgressUpdater.h"
    "${INCLUDE_F}/Random.h"
    "${INCLUDE_F}/RangedScalarDistribution.h"
    "${INCLUDE_F}/Round.h"
    "${INCLUDE_F}/StringUtil.h"
    "${INCLUDE_F}/SymmetricBitSet.h"
    "${INCLUDE_F}/SymmetricMatrix.h"
    "${INCLUDE_F}/Timer.h"
    "${INCLUDE_F}/Vectors.h")

set( SRC_FILES
    "${SRC_DIR}/Convert.cpp"
    "${SRC_DIR}/ConvexOptimiser.cpp"
    "${SRC_DIR}/CpuTimer.cpp"
    "${SRC_DIR}/Exceptions.cpp"
    "${SRC_DIR}/FileIO.cpp"
    "${SRC_DIR}/LinearRegressor.cpp"
    "${SRC_DIR}/MathUtil.cpp"
    "${SRC_DIR}/Memory.cpp"
    "${SRC_DIR}/MultiLock.cpp"
    "${SRC_DIR}/NewtonRaphson.cpp"
    "${SRC_DIR}/Pack.cpp"
    "${SRC_DIR}/ProgressDelegate.cpp"
    "${SRC_DIR}/ProgressUpdater.cpp"
    "${SRC_DIR}/Random.cpp"
    "${SRC_DIR}/RangedScalarDistribution.cpp"
    "${SRC_DIR}/StringUtil.cpp"
    "${SRC_DIR}/SymmetricBitSet.cpp"
    "${SRC_DIR}/Timer.cpp"
    "${SRC_DIR}/Vectors.cpp"
    )

add_library( ${PROJECT_NAME} ${SRC_FILES} ${INCLUDE_FILES})
include( "cmake/LinkLibs.cmake")
