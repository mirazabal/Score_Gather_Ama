cmake_minimum_required (VERSION 2.6)
project (Amazon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

include_directories(${Amazon_SOURCE_DIR})
include_directories(${Amazon_SOURCE_DIR}/include)

file(GLOB Amazon_SRC
    "*.h"
    "*.cpp"
)

add_executable(Amazon ${Amazon_SRC})

TARGET_LINK_LIBRARIES(Amazon PUBLIC pthread )

