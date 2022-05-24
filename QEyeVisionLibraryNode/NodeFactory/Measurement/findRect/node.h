#pragma once

#include <ReVisionLib/ReVision.hpp>
#include <QEyeVisionLibrary/QEyeVisionLib.hpp>

namespace qv
{
    class FindRectCaliper
    {
    public:
        std::vector<rv::RotatedRect<double>> regions;

        int threshold = 20;     //滤波系数
        rv::CaliperTransition transition = rv::CaliperTransition::Positive;         //颜色变化
        rv::CaliperResultSelection selection = rv::CaliperResultSelection::Max;     //卡尺目标
        int ignorePointCount = 0;                                                   //忽略点数量

    private:

    };

    class FindRectNode : public NodeBase
    {
    public:
        FindRectNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;


    public:
        //边缘拟合
        rv::RectMix rectMix;
        void setRectMix(const rv::RectMix& _rectMix);
        void updateRectMix();
        FindRectCaliper caliper;

    public:
        NodeParamDescription outputRect = { "OutputRect", u8"矩形", Variant::VariantType::Rect };

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
