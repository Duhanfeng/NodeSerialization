#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>
#include "shapeModelInterface.h"

namespace qv
{
    class ShapeMatchNode : public NodeBase
    {
    public:
        ShapeMatchNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;

        //模板操作
        bool createTempl(rv::InputReMat image, rv::InputRegion region);
        bool getTemplImage(rv::OutputReMat image);
        bool isTemplEmpty();
        void recoverTempl();   //在MatchParam中图片有效而id无效的情况下,根据图片和region重新创建id

    public:
        ShapeModelInterface matchModel;     //匹配模板

    public:
        NodeParamDescription outputPoses = { "Poses", u8"坐标", Variant::VariantType::Pose };
        NodeParamDescription outputScores = { "Scores", u8"分数", Variant::VariantType::Double };

    private:
        std::vector<rv::Pose<double>> resultPoses;
        std::vector<double> resultScores;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
            ar& BOOST_SERIALIZATION_NVP(matchModel);

            recoverTempl();
        }
    };

}

