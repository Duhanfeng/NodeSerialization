#pragma once

#include <opencv2/opencv.hpp>
#include "ReVision/remat.h"
#include "ReVision/region.h"
#include "../iimgproc.h"

namespace rv
{
    class ImageProc : public IImageProc
    {
    public:
        //图像裁剪
        virtual void clipImage(InputReMat src, OutputReMat dst, InputRegion region) override;
        //骨骼
        virtual void skeleton(InputReMat src, OutputReMat dst) override;
        //连通性分析
        virtual void connection(InputReMat src, std::vector<ReMat>& regions) override;
        //金字塔缩放
        virtual void buildPyramid(InputReMat src, std::vector<ReMat>& dst, int maxlevel) override;

        //导数/边缘检测
        virtual void canny(InputReMat src, OutputReMat dst, int threshold1, int threshold2) override;
        virtual void sobel(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy, int ksize) override;
        virtual void scharr(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy) override;
        virtual void laplacian(InputReMat src, OutputReMat dst, int ddepth, int ksize) override;
        virtual void spatialGradient(InputReMat src, OutputReMat dx, OutputReMat dy, int ksize) override;

    };


}