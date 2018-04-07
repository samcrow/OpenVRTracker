cmake_minimum_required(VERSION 2.8)

set(TARGET vr-test)
set(SOURCES main.cpp)

find_library(OPENVR_LIBRARIES NAMES openvr_api REQUIRED PATHS openvr/lib)
include_directories(openvr/include)
set(OPENVR_HEADERS openvr/include/openvr.h)

add_executable(${TARGET} ${SOURCES} ${OPENVR_HEADERS})
target_link_libraries(${TARGET} ${OPENVR_LIBRARIES})
target_link_libraries(${TARGET} ${CMAKE_DL_LIBS})
