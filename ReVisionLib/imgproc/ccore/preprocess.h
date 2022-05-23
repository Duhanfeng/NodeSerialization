#pragma once

#include <opencv2/opencv.hpp>
#include "remat.h"
#include "region.h"
#include "../ipreprocess.h"


namespace rv
{
    class Preprocess : public IPreprocess
    {
    public:

        //滤波
        virtual void meanImage(InputReMat src, OutputReMat dst, int kernelSize) override;
        virtual void medianImage(InputReMat src, OutputReMat dst, int kernelSize) override;
        virtual void gaussImage(InputReMat src, OutputReMat dst, int kernelSize) override;

        //二值化
        virtual void threshold(InputReMat src, OutputReMat dst, int threshold1, int threshold2) override;

        //形态学
        virtual void morphology(InputReMat src, OutputReMat dst, MorphTypes type, int kernelSize, KernShapes shape) override;

        //通道转换
        virtual void convertColor(const cv::Point3_<uchar>& src, cv::Point3_<uchar>& dst, ColorConversionCodes code) override;
        virtual void convertColor(InputReMat src, OutputReMat dst, ColorConversionCodes code) override;
        virtual void extractColorPlane(InputReMat src, OutputReMat dst, ColorPlanCodes plan) override;

        //卷积
        virtual void filter2D(InputReMat src, OutputReMat dst, int depth, InputReMat kernel) override;

        //LUT
        virtual void lut(InputReMat src, InputReMat lut, OutputReMat dst) override;

        //其他常用预处理
        virtual void equalizeHist(InputReMat src, OutputReMat dst) override;    //直方图均衡化
        virtual void invert(InputReMat src, OutputReMat dst) override;         //反相
        virtual void denoising(InputReMat src, OutputReMat dst) override;       //去噪

    private:
        void threshold(cv::InputArray src, cv::OutputArray dst, uchar threshold1, uchar threshold2);
    };

}
