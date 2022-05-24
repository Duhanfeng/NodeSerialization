#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "ReVision/region.h"
#include "ReVision/remat.h"

namespace rv
{
    struct FeatureGroupEnable
    {
        bool isEnableIntensity = true;
        bool isEnablePlaneDeviation = true;
        bool isEnableEntropyGray = true;
        bool isEnableMinMaxGray = true;
        bool isEnableSurface = true;
        bool isEnableFuzzy = true;
        bool isEnableGrayPlane = true;
        bool isEnableEllipticAxis = true;
        bool isEnableCoocFeature = true;

        //备注: 以下算法耗时不稳定,不适用于对耗时有严格要求的场景,默认关闭
        bool isEnableSobelAmpHisto = false;
        bool isEnableGrayHisto = false;
    };

    class ITexture
    {
    public:
        struct CoocMatrixFeature
        {
            double energy;
            double correlation;
            double homogeneity;
            double contrast;
        };

        enum CoocAngle
        {
            CoocAngle_0,
            CoocAngle_45,
            CoocAngle_90,
            CoocAngle_135,
        };

        struct FeatureGroup
        {
            //Intensity
            double mean = 0;
            double deviation = 0;

            //PlaneDeviation
            double planeDeviation = 0;

            //EntropyGray
            double entropy = 0;
            double anisotropy = 0;

            //MinMaxGray
            double min = 0;
            double max = 0;
            double median = 0;

            //FitSurfaceFirstOrder
            double alpha = 0;
            double beta = 0;
            double gamma = 0;

            //Fuzzy
            double fuzzyEntropy = 0;
            double fuzzyPerimeter = 0;

            //MomentsGrayPlane
            double grayPlaneRow = 0;
            double grayPlaneCol = 0;
            double grayPlaneAlpha1 = 0;
            double grayPlaneBeta = 0;
            double grayPlaneMean = 0;

            //EllipticAxisGray
            double ra = 0;
            double rb = 0;
            double phi = 0;

            //CoocFeature
            CoocMatrixFeature cooc_0;
            CoocMatrixFeature cooc_45;
            CoocMatrixFeature cooc_90;
            CoocMatrixFeature cooc_135;

            //SobelAmpHisto
            double sobelAmpHisto[32] = { 0 };

            //GrayHisto
            double grayHisto[32] = { 0 };

        };

    public:
        virtual void setImage(InputReMat remat, InputRegion region) = 0;
        virtual bool getFeature(FeatureGroup& features, const FeatureGroupEnable& enable = FeatureGroupEnable()) = 0;
        virtual int getGroupLength(const FeatureGroupEnable& enable = FeatureGroupEnable()) = 0;
        virtual bool getFeature(std::vector<double>& feature, const FeatureGroupEnable& enable = FeatureGroupEnable());

        static cv::Ptr<ITexture> create(bool useHCore = true);
    };

}
