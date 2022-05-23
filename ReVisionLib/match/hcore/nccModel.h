#pragma once

#include "remat.h"
#include "../imatch.h"
#include <HalconCpp.h>
#include <opencv2/opencv.hpp>
#include <vector>

namespace rv
{
    class HNccModel : public INccModel
    {
#pragma region 基本控制
    public:

        //创建/释放
        virtual bool create(InputReMat image, InputRegion region) override;
        virtual bool create(InputReMat image, InputRegion region, const IsotropicScaling& scaling) override;
        virtual bool create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling) override;
        virtual void clear() override;

        virtual bool find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const override;

        static bool find(InputReMat image, InputRegion region, const std::vector<const HNccModel*>& models, std::vector<MatchResult>& results);

#pragma endregion

#pragma region 参数配置
    public:

        //角度
        virtual double angleStart() const override;
        virtual void setAngleStart(double value) override;
        virtual double angleEnd() const override;
        virtual void setAngleEnd(double value) override;

        //匹配分数
        virtual double minScore() const override;
        virtual void setMinScore(double value) override;

        //查找数量
        virtual int numMatches() const override;
        virtual void setNumMatches(int value) override;

        //最大重叠度
        virtual double maxOverlap() const override;
        virtual void setMaxOverlap(double value) override;

        //原点偏移
        virtual void getOrigin(cv::Point2d& originOffset, double& angle) const override;
        virtual void setOrigin(const cv::Point2d& originOffset, double angle) override;

    protected:
        struct NccMatchParam
        {
            double angleStart = -10 * CV_PI / 180;  //开始角度
            double angleEnd = 350 * CV_PI / 180;    //角度范围
            double minScore{ 0.6 };                 //最小匹配分数
            int numMatches{ 0 };                    //最大匹配数量,0为不限制
            double maxOverlap{ 0.6 };               //最大重叠度
            double angle{ 0 };                      //角度偏移
        };
        NccMatchParam matchParam;

#pragma endregion

#pragma region 模板参数

    public:
        virtual bool isCreated() const override;
        virtual ScalingMode scalingMode() const override;
        virtual IsotropicScaling isotropicScaling() const override;
        virtual AnisotropicScaling anisotropicScaling() const override;
        virtual ReMat templImage() const override;
        virtual Region templRegion() const override;

#pragma endregion

    protected:
        HalconCpp::HNCCModel m_nccModel;

        //序列化反序列化所用数据
        ScalingMode m_scalingMode = ScalingMode::None;
        IsotropicScaling m_isotropicScaling;
        AnisotropicScaling m_anisotropicScaling;
        ReMat m_image;
        Region m_region;
    };

}

