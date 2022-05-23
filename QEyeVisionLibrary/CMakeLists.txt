cmake_minimum_required (VERSION 3.8)

project ("QEyeVisionLibrary")

include_directories (${CMAKE_SOURCE_DIR})                   # 根目录
include_directories (${CMAKE_SOURCE_DIR}/ReVisionLib)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})           # 当前目录
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/VisionFlow)

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

# 视觉框架核心
file(GLOB_RECURSE qv_frame_src VisionFlow/*.c VisionFlow/*.cpp VisionFlow/*.h VisionFlow/*.hpp)

# 编译生成
add_library(${PROJECT_NAME} ${qv_frame_src})
target_link_libraries(${PROJECT_NAME} ReVisionLib)
