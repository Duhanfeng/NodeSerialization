#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    enum class GrayThresholdMode
    {
        Drak = 0,
        Bright,
        Double,
        AutoThreshold,
    };

    class ThresholdNode : public NodeBase
    {
    public:
        ThresholdNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;

    public:
        GrayThresholdMode thresholdMode = GrayThresholdMode::Bright;
        unsigned char threshold1 = 125;
        unsigned char threshold2 = 255;

    public:
        NodeParamDescription outputImage = { "Output", u8"图像", Variant::VariantType::Image };

    private:
        cv::Ptr<rv::IPreprocess> IPreprocess = nullptr;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
            ar& BOOST_SERIALIZATION_NVP(thresholdMode);
            ar& BOOST_SERIALIZATION_NVP(threshold1);
            ar& BOOST_SERIALIZATION_NVP(threshold2);
        }
    };

}

//BOOST_CLASS_EXPORT(qv::ThresholdNode)