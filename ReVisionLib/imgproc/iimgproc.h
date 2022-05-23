#pragma once

#include <opencv2/opencv.hpp>
#include "remat.h"
#include "region.h"

namespace rv
{
    class IImageProc
    {
    public:

        //图像裁剪
        virtual void clipImage(InputReMat src, OutputReMat dst, InputRegion region) = 0;
        //骨骼
        virtual void skeleton(InputReMat src, OutputReMat dst) = 0;
        //连通性分析
        virtual void connection(InputReMat image, std::vector<ReMat>& regions) = 0;
        //金字塔缩放
        virtual void buildPyramid(InputReMat src, std::vector<ReMat>& dst, int maxlevel) = 0;

        //颜色转换
        
        //导数/边缘检测
        virtual void canny(InputReMat src, OutputReMat dst, int threshold1, int threshold2) = 0;
        virtual void sobel(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy, int ksize) = 0;
        virtual void scharr(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy) = 0;
        virtual void laplacian(InputReMat src, OutputReMat dst, int ddepth, int ksize) = 0;
        virtual void spatialGradient(InputReMat src, OutputReMat dx, OutputReMat dy, int ksize) = 0;

        static cv::Ptr<IImageProc> create(bool useHCore = true);
    };

}
