
cmake_minimum_required (VERSION 3.8)

project ("ReVisionLib")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}) # 当前目录

# geometry
file(GLOB geometry_src geometry/*.cpp geometry/*.h geometry/*.hpp)
message(geometry_src: ${geometry_src})

# 视觉算法库
set(rv_src
    ${geometry_src}
    revision.hpp
    hmat.h
    remat.cpp
    remat.h
    region.cpp
    region.h
    rmath.h
    irewindow.h

    # 预处理
    imgproc/iimgproc.cpp
    imgproc/iimgproc.h
    imgproc/ipreprocess.cpp
    imgproc/ipreprocess.h
    imgproc/ccore/imgproc.cpp
    imgproc/ccore/imgproc.h
    imgproc/ccore/preprocess.cpp
    imgproc/ccore/preprocess.h

    # 特征
    feature/contour/icontour.cpp
    feature/contour/icontour.h
    feature/texture/itexture.cpp
    feature/texture/itexture.h

    # 分类器
    classifier/iclassifier.cpp
    classifier/iclassifier.h
    classifier/ccore/mlp/classifier_mlp.cpp
    classifier/ccore/mlp/classifier_mlp.h

    # 匹配
    match/imatch.cpp
    match/imatch.h

    # 测量
    #measure/fit/ifit.cpp
    #measure/fit/ifit.h
    #measure/fit/ccore/fit.cpp
    #measure/fit/ccore/fit.h
    measure/imeasure.h

    # 模块
    modules/textureClassifier/itextureClassifier.cpp
    modules/textureClassifier/itextureClassifier.h

)

if (USE_HCORE)
    set(rv_src ${rv_src}

        # 特征
        feature/texture/hcore/htexture.cpp
        feature/texture/hcore/htexture.h

        # 分类器
        classifier/hcore/mlp/hclassifier_mlp.cpp
        classifier/hcore/mlp/hclassifier_mlp.h
        
        # 匹配
        match/hcore/shapeModel.cpp
        match/hcore/shapeModel.h
        match/hcore/genericShapeModel.cpp
        match/hcore/genericShapeModel.h
        match/hcore/nccModel.cpp
        match/hcore/nccModel.h
        match/hcore/matchInterface.cpp
        match/hcore/matchInterface.h

    )
endif ()

# 编译生成
add_library(${PROJECT_NAME} ${rv_src})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${H_LIB})
