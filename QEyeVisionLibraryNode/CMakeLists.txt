cmake_minimum_required (VERSION 3.8)

project ("QEyeVisionLibraryNode")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    NodeFactory/Preprocess/threshold/node.h
    NodeFactory/Preprocess/threshold/node.cpp
    NodeFactory/Preprocess/smoothness/node.h
    NodeFactory/Preprocess/smoothness/node.cpp
    NodeFactory/Preprocess/morphology/node.h
    NodeFactory/Preprocess/morphology/node.cpp
    NodeFactory/Preprocess/imageProcess/node.h
    NodeFactory/Preprocess/imageProcess/node.cpp
    NodeFactory/Preprocess/colorConvert/node.h
    NodeFactory/Preprocess/colorConvert/node.cpp

    NodeFactory/Location/colorFind/node.h
    NodeFactory/Location/colorFind/node.cpp
    NodeFactory/Location/nccMatch/node.h
    NodeFactory/Location/nccMatch/node.cpp
    NodeFactory/Location/nccMatch/nccModelInterface.h
    NodeFactory/Location/nccMatch/nccModelInterface.cpp
    NodeFactory/Location/shapeMatch/node.h
    NodeFactory/Location/shapeMatch/node.cpp
    NodeFactory/Location/shapeMatch/shapeModelInterface.h
    NodeFactory/Location/shapeMatch/shapeModelInterface.cpp

    NodeFactory/Measurement/findCircle/node.h
    NodeFactory/Measurement/findCircle/node.cpp
    NodeFactory/Measurement/findLine/node.h
    NodeFactory/Measurement/findLine/node.cpp
    NodeFactory/Measurement/findRect/node.h
    NodeFactory/Measurement/findRect/node.cpp

)

# 包含子项目(由于DataCode包含的文件比较多,单独打包)
add_subdirectory ("NodeFactory/ID/dataCode")

# 应用,启动界面
file(GLOB lib_src NodeFactory/*.cpp NodeFactory/*.h NodeFactory/*.hpp)

# 编译生成
add_library(${PROJECT_NAME} ${lib_src} ${node_src} "QEyeVisionLibraryNode.hpp")
target_link_libraries(${PROJECT_NAME} QEyeVisionLibrary DataCodeNode)
