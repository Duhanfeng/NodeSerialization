#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    class MorphologyNode : public NodeBase
    {
    public:
        MorphologyNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;

    public:
        int kernelSize = 3;
        rv::IPreprocess::MorphTypes morphTypes = rv::IPreprocess::MorphTypes::Dilate;
        rv::IPreprocess::KernShapes kernShapes = rv::IPreprocess::KernShapes::Rectangle;

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
            ar& BOOST_SERIALIZATION_NVP(kernelSize);
            ar& BOOST_SERIALIZATION_NVP(morphTypes);
            ar& BOOST_SERIALIZATION_NVP(kernShapes);
        }
    };

}

