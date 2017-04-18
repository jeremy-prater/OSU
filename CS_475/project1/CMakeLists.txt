
cmake_minimum_required (VERSION 3.1)

set (PROJ_NAME cs475-project1)

project (${PROJ_NAME})

# Add include folders
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/platform/include")

set(PLATFORM_SRCS
  ${PROJECT_SOURCE_DIR}/platform/src/CSVLogger.cpp
  ${PROJECT_SOURCE_DIR}/platform/src/ThreadManager.cpp
)

set(PROJECT_SRCS
  ${PROJECT_SOURCE_DIR}/src/project1.cpp
  ${PROJECT_SOURCE_DIR}/src/curveCalc.cpp
)

add_executable(${PROJ_NAME} ${PLATFORM_SRCS} ${PROJECT_SRCS})
