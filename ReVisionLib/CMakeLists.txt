
cmake_minimum_required (VERSION 3.8)

project ("ReVisionLib")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}) # 当前目录

# geometry
file(GLOB geometry_src ReVision/geometry/*.cpp ReVision/geometry/*.h ReVision/geometry/*.hpp)
message(geometry_src: ${geometry_src})

# 视觉算法库
set(rv_src
    ${geometry_src}
    ReVision/hmat.h
    ReVision/remat.cpp
    ReVision/remat.h
    ReVision/region.cpp
    ReVision/region.h
    ReVision/rmath.h
    ReVision/irewindow.h

    # 预处理
    ReVision/imgproc/iimgproc.cpp
    ReVision/imgproc/iimgproc.h
    ReVision/imgproc/ipreprocess.cpp
    ReVision/imgproc/ipreprocess.h
    ReVision/imgproc/ccore/imgproc.cpp
    ReVision/imgproc/ccore/imgproc.h
    ReVision/imgproc/ccore/preprocess.cpp
    ReVision/imgproc/ccore/preprocess.h

    # 特征
    ReVision/feature/contour/icontour.cpp
    ReVision/feature/contour/icontour.h
    ReVision/feature/texture/itexture.cpp
    ReVision/feature/texture/itexture.h

    # 分类器
    ReVision/classifier/iclassifier.cpp
    ReVision/classifier/iclassifier.h
    ReVision/classifier/ccore/mlp/classifier_mlp.cpp
    ReVision/classifier/ccore/mlp/classifier_mlp.h

    # 匹配
    ReVision/match/imatch.cpp
    ReVision/match/imatch.h

    # 测量
    #measure/fit/ifit.cpp
    #measure/fit/ifit.h
    #measure/fit/ccore/fit.cpp
    #measure/fit/ccore/fit.h
    ReVision/measure/imeasure.h

    # 模块
    ReVision/modules/textureClassifier/itextureClassifier.cpp
    ReVision/modules/textureClassifier/itextureClassifier.h

)

if (USE_HCORE)
    set(rv_src ${rv_src}

        # 特征
        ReVision/feature/texture/hcore/htexture.cpp
        ReVision/feature/texture/hcore/htexture.h

        # 分类器
        ReVision/classifier/hcore/mlp/hclassifier_mlp.cpp
        ReVision/classifier/hcore/mlp/hclassifier_mlp.h
        
        # 匹配
        ReVision/match/hcore/shapeModel.cpp
        ReVision/match/hcore/shapeModel.h
        ReVision/match/hcore/genericShapeModel.cpp
        ReVision/match/hcore/genericShapeModel.h
        ReVision/match/hcore/nccModel.cpp
        ReVision/match/hcore/nccModel.h
        ReVision/match/hcore/matchInterface.cpp
        ReVision/match/hcore/matchInterface.h

    )
endif ()

# 编译生成
add_library(${PROJECT_NAME} ${rv_src} "ReVision.hpp")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${H_LIB})
