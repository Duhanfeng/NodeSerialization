#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    enum class ImageProcessMethod
    {
        EqualizeHist = 0,
        Invert,
    };

    class ImageProcessNode : public NodeBase
    {
    public:
        ImageProcessNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;

    public:
        ImageProcessMethod method = ImageProcessMethod::EqualizeHist;

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
            ar& BOOST_SERIALIZATION_NVP(method);
        }
    };

}

BOOST_CLASS_EXPORT(qv::ImageProcessNode)
