#pragma once

#include <ReVisionLib/ReVision.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入

namespace qv
{
    class NccModelInterface : public rv::INccModel
    {
    public:

        NccModelInterface();

        //创建/释放
        virtual bool create(rv::InputReMat image, rv::InputRegion region) override;
        virtual bool create(rv::InputReMat image, rv::InputRegion region, const rv::IsotropicScaling& scaling) override;
        virtual bool create(rv::InputReMat image, rv::InputRegion region, const rv::AnisotropicScaling& scaling) override;
        virtual void clear() override;

        //查找
        virtual bool find(rv::InputReMat image, rv::InputRegion region, std::vector<rv::MatchResult>& results) const override;

        //信息
        virtual bool isCreated() const override;
        virtual rv::ScalingMode scalingMode() const override;
        virtual rv::IsotropicScaling isotropicScaling() const override;
        virtual rv::AnisotropicScaling anisotropicScaling() const override;
        virtual rv::ReMat templImage() const override;
        virtual rv::Region templRegion() const override;

        //运行时参数
        virtual double angleStart() const override;
        virtual void setAngleStart(double value) override;   //弧度制
        virtual double angleEnd() const override;
        virtual void setAngleEnd(double value) override;     //弧度制
        virtual double minScore() const override;
        virtual void setMinScore(double value) override;     //[0-1]
        virtual int numMatches() const override;
        virtual void setNumMatches(int value) override;      //0代表不限制
        virtual double maxOverlap() const override;
        virtual void setMaxOverlap(double value) override;   //[0-1]
        virtual void getOrigin(cv::Point2d& originOffset, double& angle) const override;       //弧度制
        virtual void setOrigin(const cv::Point2d& originOffset, double angle) override;

    private:
        cv::Ptr<rv::INccModel> INccModel = nullptr;
        cv::Ptr<rv::MatchInterface> MatchInterface = nullptr;
    };

}


BOOST_SERIALIZATION_SPLIT_FREE(qv::NccModelInterface)

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        void save(Archive& ar, const ::qv::NccModelInterface& model, const unsigned int version)
        {
            bool isCreated = model.isCreated();
            ::rv::ScalingMode scalingMode = model.scalingMode();
            ::rv::IsotropicScaling isotropicScaling = model.isotropicScaling();
            ::rv::AnisotropicScaling anisotropicScaling = model.anisotropicScaling();
            ::rv::ReMat templImage = model.templImage();
            ::rv::Region templRegion = model.templRegion();

            //保存模板基本要素
            ar& BOOST_SERIALIZATION_NVP(isCreated);
            ar& BOOST_SERIALIZATION_NVP(scalingMode);
            ar& BOOST_SERIALIZATION_NVP(isotropicScaling);
            ar& BOOST_SERIALIZATION_NVP(anisotropicScaling);
            ar& BOOST_SERIALIZATION_NVP(templImage);
            ar& BOOST_SERIALIZATION_NVP(templRegion);

            double angleStart = model.angleStart();
            double angleEnd = model.angleEnd();
            double minScore = model.minScore();
            int numMatches = model.numMatches();
            double maxOverlap = model.maxOverlap();
            cv::Point2d originOffset;
            double angle;
            model.getOrigin(originOffset, angle);

            //保存模板运行时参数
            ar& BOOST_SERIALIZATION_NVP(angleStart);
            ar& BOOST_SERIALIZATION_NVP(angleEnd);
            ar& BOOST_SERIALIZATION_NVP(minScore);
            ar& BOOST_SERIALIZATION_NVP(numMatches);
            ar& BOOST_SERIALIZATION_NVP(maxOverlap);
            ar& BOOST_SERIALIZATION_NVP(originOffset);
            ar& BOOST_SERIALIZATION_NVP(angle);

        }

        template <class Archive>
        void load(Archive& ar, ::qv::NccModelInterface& model, const unsigned int version)
        {
            bool isCreated;
            ::rv::ScalingMode scalingMode;
            ::rv::IsotropicScaling isotropicScaling;
            ::rv::AnisotropicScaling anisotropicScaling;
            ::rv::ReMat templImage;
            ::rv::Region templRegion;

            ar& BOOST_SERIALIZATION_NVP(isCreated);
            ar& BOOST_SERIALIZATION_NVP(scalingMode);
            ar& BOOST_SERIALIZATION_NVP(isotropicScaling);
            ar& BOOST_SERIALIZATION_NVP(anisotropicScaling);
            ar& BOOST_SERIALIZATION_NVP(templImage);
            ar& BOOST_SERIALIZATION_NVP(templRegion);

            double angleStart;
            double angleEnd;
            double minScore;
            int numMatches;
            double maxOverlap;
            cv::Point2d originOffset;
            double angle;

            ar& BOOST_SERIALIZATION_NVP(angleStart);
            ar& BOOST_SERIALIZATION_NVP(angleEnd);
            ar& BOOST_SERIALIZATION_NVP(minScore);
            ar& BOOST_SERIALIZATION_NVP(numMatches);
            ar& BOOST_SERIALIZATION_NVP(maxOverlap);
            ar& BOOST_SERIALIZATION_NVP(originOffset);
            ar& BOOST_SERIALIZATION_NVP(angle);

            //还原模板状态
            if (isCreated)
            {
                switch (scalingMode)
                {
                case ::rv::ScalingMode::None:
                    model.create(templImage, templRegion);
                    break;
                case ::rv::ScalingMode::Isotropic:
                    model.create(templImage, templRegion, isotropicScaling);
                    break;
                case ::rv::ScalingMode::Anisotropic:
                    model.create(templImage, templRegion, anisotropicScaling);
                    break;
                default:
                    break;
                }

                if (model.isCreated())
                {
                    model.setAngleStart(angleStart);
                    model.setAngleEnd(angleEnd);
                    model.setMinScore(minScore);
                    model.setNumMatches(numMatches);
                    model.setMaxOverlap(maxOverlap);
                    model.setOrigin(originOffset, angle);
                }
            }

        }
    }
}