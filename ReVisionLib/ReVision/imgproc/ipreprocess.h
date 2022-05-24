#pragma once

#include <opencv2/opencv.hpp>
#include "ReVision/remat.h"

namespace rv
{
    /*
    预处理: 
        1. 操作针对整个图像,不存在只操作某region的情况;
        2. 输入图像和输出图像的尺寸应当保持一致;
        3. 相对于src,dst应当为新开辟的内存;
    */
    class IPreprocess
    {
    public:
        enum KernShapes
        {
            Rectangle = 0,
            Circle
        };

        enum MorphTypes
        {
            Dilate = 0, //膨胀
            Erode,      //腐蚀
            Close,      //关运算
            Open,       //开运算
            Gradient,   //梯度
            TopHat,     //顶帽
            BlackHat    //黑帽
        };

        enum ColorConversionCodes
        {
            RGB2GRAY = 0,
            RGB2BGR,
            RGB2HSV,
            RGB2HLS,

            BGR2GRAY,
            BGR2RGB,
            BGR2HSV,
            BGR2HLS,

            GRAY2RGB,
            GRAY2BGR,
            HSV2BGR,
            HSV2RGB,
        };

        enum ColorPlanCodes
        {
            Gray = 0,
            BGR_B,
            BGR_G,
            BGR_R,
            HSV_H,
            HSV_S,
            HSV_V,
        };

    public:

        //滤波
        virtual void meanImage(InputReMat src, OutputReMat dst, int kernelSize) = 0;
        virtual void medianImage(InputReMat src, OutputReMat dst, int kernelSize) = 0;
        virtual void gaussImage(InputReMat src, OutputReMat dst, int kernelSize) = 0;

        //二值化
        virtual void threshold(InputReMat src, OutputReMat dst, int threshold1, int threshold2) = 0;

        //形态学
        virtual void morphology(InputReMat src, OutputReMat dst, MorphTypes type, int kernelSize, KernShapes shape) = 0;

        //通道转换
        virtual void convertColor(const cv::Point3_<uchar>& src, cv::Point3_<uchar>& dst, ColorConversionCodes code) = 0;
        virtual void convertColor(InputReMat src, OutputReMat dst, ColorConversionCodes code) = 0;
        virtual void extractColorPlane(InputReMat src, OutputReMat dst, ColorPlanCodes plan) = 0;

        //卷积
        virtual void filter2D(InputReMat src, OutputReMat dst, int depth, InputReMat kernel) = 0;

        //LUT
        virtual void lut(InputReMat src, InputReMat lut, OutputReMat dst) = 0;

        //其他常用预处理
        virtual void equalizeHist(InputReMat src, OutputReMat dst) = 0;     //直方图均衡化
        virtual void invert(InputReMat src, OutputReMat dst) = 0;           //反相
        virtual void denoising(InputReMat src, OutputReMat dst) = 0;        //去噪

        static cv::Ptr<IPreprocess> create(bool useHCore = true);
    };

}
