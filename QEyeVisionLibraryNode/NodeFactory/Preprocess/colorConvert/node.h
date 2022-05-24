#pragma once

#include <ReVisionLib/ReVision.hpp>
#include <QEyeVisionLibrary/QEyeVisionLib.hpp>

namespace qv
{
    class ColorConvertNode : public NodeBase
    {
    public:
        ColorConvertNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;

    public:
        rv::IPreprocess::ColorConversionCodes code1 = rv::IPreprocess::ColorConversionCodes::BGR2GRAY;
        rv::IPreprocess::ColorPlanCodes code2 = rv::IPreprocess::ColorPlanCodes::Gray;
        bool isConversion = true;

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
            ar& BOOST_SERIALIZATION_NVP(code1);
            ar& BOOST_SERIALIZATION_NVP(code2);
            ar& BOOST_SERIALIZATION_NVP(isConversion);
        }
    };

}
