#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    class ColorTempl
    {
    public:
        cv::Point3_<uchar> hsv;
        double distance{ 0 };

        ColorTempl(){}
        ColorTempl(const cv::Point3_<uchar>& _hsv, double _distance): hsv(_hsv) , distance(_distance)
        {}
    };

    class ColorFindNode : public NodeBase
    {
    public:
        ColorFindNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;

    public:
        std::vector<ColorTempl> colorTempls;
        void hsv2bgr(const cv::Point3_<uchar>& src, cv::Point3_<uchar>& dst);
        void bgr2hsv(const cv::Point3_<uchar>& src, cv::Point3_<uchar>& dst);

    public:
        NodeParamDescription outputPoses = { "Poses", u8"坐标", Variant::VariantType::Pose };
        NodeParamDescription outputScores = { "Scores", u8"分数", Variant::VariantType::Double };

    private:
        cv::Ptr<rv::IPreprocess> IPreprocess = nullptr;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
            ar& BOOST_SERIALIZATION_NVP(colorTempls);
        }
    };

}

namespace boost
{
    namespace serialization
    {
        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::qv::ColorTempl& data, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(data.hsv);
            ar& BOOST_SERIALIZATION_NVP(data.distance);
        }
    }
}
