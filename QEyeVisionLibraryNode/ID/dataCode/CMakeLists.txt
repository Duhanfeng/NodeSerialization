cmake_minimum_required (VERSION 3.8)

project ("DataCodeNode")
include_directories (${CMAKE_SOURCE_DIR})                   # 根目录
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

# 添加zbar
if (WIN32)
    set(ZBAR_ROOT "C:/Program Files/CppLibrary/ZBar")
    set(ZBAR_LIBS ${ZBAR_ROOT}/lib/libzbar64-0.lib)
    include_directories(${ZBAR_ROOT}/include)
    link_directories(${ZBAR_ROOT}/lib)
else()
    set(ZBAR_LIBS /usr/lib/arm-linux-gnueabihf/libzbar.so)
    include_directories(/usr/include/zbar.h)
endif()
link_libraries(${ZBAR_LIBS})

# 添加wechat_qrcode
include_directories(wechat_qrcode/include)
file(GLOB_RECURSE wechat_qrcode_src wechat_qrcode/src/*.cpp wechat_qrcode/src/*.hpp)

# 视觉框架核心
file(GLOB node_src *.c *.cpp *.h *.hpp)

# 编译生成
add_library(${PROJECT_NAME} ${node_src} ${wechat_qrcode_src})
target_link_libraries(${PROJECT_NAME} QEyeVisionLibrary)
