cmake_minimum_required (VERSION 3.8)

project ("QEyeVisionLibraryNode")

include_directories (${CMAKE_SOURCE_DIR})                   # 根目录
include_directories (${CMAKE_SOURCE_DIR}/ReVisionLib)
include_directories (${CMAKE_SOURCE_DIR}/QEyeVisionLibrary)

# 添加boost支持
if (WIN32)
    include_directories("C:/Program Files/CppLibrary/boost/include/boost-1_75")
    link_directories("C:/Program Files/CppLibrary/boost/lib")
    if(${CMAKE_BUILD_TYPE} STREQUAL Release)
        set(BOOST_SERIALIZATION_LIB "libboost_serialization-vc142-mt-x64-1_75")
    else()
        set(BOOST_SERIALIZATION_LIB "libboost_serialization-vc142-mt-gd-x64-1_75")
    endif()
else()
    find_package(Boost REQUIRED)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        set(BOOST_SERIALIZATION_LIB "/usr/lib/arm-linux-gnueabihf/libboost_serialization.so")
    endif()
endif()
link_libraries(${BOOST_SERIALIZATION_LIB})

set(node_src
    Preprocess/threshold/node.h
    Preprocess/threshold/node.cpp
    Preprocess/smoothness/node.h
    Preprocess/smoothness/node.cpp
    Preprocess/morphology/node.h
    Preprocess/morphology/node.cpp
    Preprocess/imageProcess/node.h
    Preprocess/imageProcess/node.cpp
    Preprocess/colorConvert/node.h
    Preprocess/colorConvert/node.cpp

    Location/colorFind/node.h
    Location/colorFind/node.cpp
    Location/nccMatch/node.h
    Location/nccMatch/node.cpp
    Location/shapeMatch/node.h
    Location/shapeMatch/node.cpp

    Measurement/findCircle/node.h
    Measurement/findCircle/node.cpp
    Measurement/findLine/node.h
    Measurement/findLine/node.cpp
    Measurement/findRect/node.h
    Measurement/findRect/node.cpp

)

# 包含子项目。
add_subdirectory ("ID/dataCode")

# 编译生成
add_library(${PROJECT_NAME} ${node_src})
target_link_libraries(${PROJECT_NAME} QEyeVisionLibrary DataCodeNode)
