#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    class FindLineCaliper
    {
    public:
        std::vector<rv::RotatedRect<double>> regions;

        int threshold = 20;     //滤波系数
        rv::CaliperTransition transition = rv::CaliperTransition::Positive;         //颜色变化
        rv::CaliperResultSelection selection = rv::CaliperResultSelection::Max;     //卡尺目标
        int ignorePointCount = 0;                                                   //忽略点数量

    private:

    };

    class FindLineNode : public NodeBase
    {
    public:
        FindLineNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;

    public:
        //边缘拟合
        FindLineCaliper caliper;

    public:
        NodeParamDescription outputLine = { "OutputLine", u8"直线", Variant::VariantType::Line };

    private:
        cv::Ptr<rv::IPreprocess> IPreprocess = nullptr;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
        }
    };

}

BOOST_CLASS_EXPORT(qv::FindLineNode)
