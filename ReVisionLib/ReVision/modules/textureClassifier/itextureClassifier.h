#pragma once

#include "ReVision/classifier/iclassifier.h"
#include "ReVision/feature/texture/itexture.h"
#include "ReVision/remat.h"
#include "ReVision/region.h"

#include <opencv2/opencv.hpp>

namespace rv
{
    class ITextureClassifier
    {
    public:
        ITextureClassifier(int classNum, IClassifier::Preprocessing preProcessing, int componentNum);

        void addSample(InputReMat image, InputRegion region, int classID);
        double train();
        int classify(InputReMat image, InputRegion region, double& confidence);

        static cv::Ptr<ITextureClassifier> create(int classNum, IClassifier::Preprocessing preProcessing, int componentNum, bool useHCore = true);

    protected:
        cv::Ptr<IClassifier> m_classifier;
        cv::Ptr<ITexture> m_texture;
        bool m_isInited{ false };

        int m_classNum{ 0 };
    };

}
