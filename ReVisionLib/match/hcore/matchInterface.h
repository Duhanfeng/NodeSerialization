#pragma once

#include "remat.h"
#include "../imatch.h"
#include <HalconCpp.h>
#include <opencv2/opencv.hpp>
#include <vector>

namespace rv
{
    class HMatchInterface : public MatchInterface
    {
    public:

        //创建模板
        virtual cv::Ptr<IShapeModel> createShapeModel() override;
        virtual cv::Ptr<INccModel> createNccModel() override;
        virtual cv::Ptr<IColorModel> createColorModel() override;

        //查找
        virtual bool find(InputReMat image, InputRegion region, const IModel& model, std::vector<MatchResult>& results) const override;
        virtual bool find(InputReMat image, InputRegion region, const std::vector<IModel>& models, std::vector<MatchResult>& results) override;

    };
}