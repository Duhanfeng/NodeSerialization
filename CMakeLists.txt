# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("NodeSerialization")

option(USE_HCORE "Use hcore opera" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BUILD_TYPE "Release")

if (WIN32)
    # 设置为release模式,在vs编译器编译的情况下,debug模式和release模式的性能存在较大的差异
    set(CMAKE_BUILD_TYPE "Release")

    # 开启此选项,可以在release模式下进行debug调试
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

else()

endif()


# 添加opencv支持
if (WIN32)
    set(OpenCV_DIR "C:/Program Files/CppLibrary/opencv/build")
    if((MSVC_VERSION EQUAL 1910) OR (MSVC_VERSION GREATER 1910))
        set(OpenCV_RUNTIME vc15)
    else()
        set(OpenCV_RUNTIME vc14)
    endif()
else()
    set(OpenCV_DIR "/usr/lib/x86_64-linux-gnu/cmake/opencv4")
endif()
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "The OpenCV lib is found!") 
    message(OpenCV_LIBS: ${OpenCV_LIBS})
    message(OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS})
    message(OpenCV_COMPUTE_CAPABILITIES: ${OpenCV_COMPUTE_CAPABILITIES})
    message(OpenCV_ANDROID_NATIVE_API_LEVEL: ${OpenCV_ANDROID_NATIVE_API_LEVEL})
    message(OpenCV_VERSION: ${OpenCV_VERSION})
    message(OpenCV_SHARED: ${OpenCV_SHARED})
    message(OpenCV_INSTALL_PATH: ${OpenCV_INSTALL_PATH})
    message(OpenCV_LIB_COMPONENTS: ${OpenCV_LIB_COMPONENTS})
    message(OpenCV_USE_MANGLED_PATHS: ${OpenCV_USE_MANGLED_PATHS})
else()
    message(STATUS "The OpenCV lib is no found!") 
endif()

# 添加hcore
message(USE_HCORE:${USE_HCORE})
if (USE_HCORE)
    message("ENABLE_HCORE")

    # 添加halcon
    include_directories("$ENV{HALCONROOT}/include")
    include_directories("$ENV{HALCONROOT}/include/halconcpp")
    link_directories("$ENV{HALCONROOT}/lib/$ENV{HALCONARCH}")
    set(H_LIB "halcon" "halconcpp")

    message(HALCONROOT: $ENV{HALCONROOT})
    add_definitions(-D ENABLE_HCORE)
else()
    message("DISABLE_HCORE")
endif ()

# 包含子项目。
add_subdirectory ("ReVisionLib")
add_subdirectory ("QEyeVisionLibrary")
add_subdirectory ("QEyeVisionLibraryNode")
add_subdirectory ("NodeSerialization")
