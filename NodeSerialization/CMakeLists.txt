# CMakeList.txt: NodeSerialization 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


project ("NodeSerialization")

include_directories (${CMAKE_SOURCE_DIR})                   # 根目录
include_directories (${CMAKE_SOURCE_DIR}/ReVisionLib)
include_directories (${CMAKE_SOURCE_DIR}/QEyeVisionLibrary)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})           # 当前目录

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

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

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} "main.cpp"  "serialization.h" "nodeBase.h" "node_A.h" "node_B.h" "node_C.h" "flowunit.h" "qeyeTest.h" "node_A.cpp" "node_B.cpp" "node_C.cpp")

target_link_libraries(${PROJECT_NAME} ReVisionLib QEyeVisionLibrary QEyeVisionLibraryNode)
