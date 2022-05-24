#include "nccModel.h"
#include "ReVision/rmath.h"

namespace rv
{
#pragma region 基本控制

    bool HNccModel::create(InputReMat image, InputRegion region)
    {
        try
        {
            //裁剪图像
            HalconCpp::HImage himage = image.getHMat();
            HalconCpp::HObject hregion = region.toHMat();
            if (hregion.IsInitialized() && (hregion.CountObj() > 0))
            {
                himage = himage.ReduceDomain(hregion);
            }

            m_image = image.clone();
            m_region = region.clone();
            m_scalingMode = ScalingMode::None;
            m_isotropicScaling = IsotropicScaling();
            m_anisotropicScaling = AnisotropicScaling();

            m_nccModel.Clear();
            m_nccModel.CreateNccModel(himage,"auto", -0.39, 6.29, "auto", "use_polarity");

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    bool HNccModel::create(InputReMat image, InputRegion region, const IsotropicScaling& scaling)
    {
        
        return create(image, region);
    }

    bool HNccModel::create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling)
    {

        return create(image, region);
    }

    void HNccModel::clear()
    {
        m_nccModel.Clear();

    }

    bool HNccModel::find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const
    {
        results.clear();

        if (m_nccModel.GetHandle() == 0)
        {
            return false;
        }

        try
        {
            HalconCpp::HImage himage = image.getHMat();

            //裁剪图像
            HalconCpp::HObject hregion = region.toHMat();
            if (hregion.IsInitialized() && (hregion.CountObj() > 0))
            {
                himage = himage.ReduceDomain(hregion);
            }


            HalconCpp::HTuple hrow;
            HalconCpp::HTuple hcolumn;
            HalconCpp::HTuple hangle;
            HalconCpp::HTuple hscore;
            double angleExtent = matchParam.angleEnd - matchParam.angleStart;
            while (angleExtent < 0)
            {
                angleExtent += deg2rad<double>(360.0);
            }
            while (angleExtent > deg2rad<double>(360.0))
            {
                angleExtent -= deg2rad<double>(360.0);
            }
            m_nccModel.FindNccModel(himage, matchParam.angleStart, angleExtent, matchParam.minScore, matchParam.numMatches, matchParam.maxOverlap, "true", 0, &hrow, &hcolumn, &hangle, &hscore);

            for (int i = 0; i < (int)hrow.Length(); i++)
            {
                MatchResult result;
                result.x = hcolumn[i].D();
                result.y = hrow[i].D();
                result.angle = -hangle[i].D() + matchParam.angle;
                result.score = hscore[i].D();
                result.modelIdentifier = std::to_string(m_nccModel.GetHandle());
                results.push_back(result);
            }

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    bool HNccModel::find(InputReMat image, InputRegion region, const std::vector<const HNccModel*>& models, std::vector<MatchResult>& results)
    {
        results.clear();

        if (models.size() == 0)
        {
            return false;
        }

        try
        {
            const NccMatchParam& matchParam = models[0]->matchParam;

            HalconCpp::HImage himage = image.getHMat();

            //裁剪图像
            HalconCpp::HObject hregion = region.toHMat();
            if (hregion.IsInitialized() && (hregion.CountObj() > 0))
            {
                himage = himage.ReduceDomain(hregion);
            }

            double angleExtent = matchParam.angleEnd - matchParam.angleStart;
            while (angleExtent <= 0)
            {
                angleExtent += deg2rad(360);
            }
            while (angleExtent > deg2rad(360))
            {
                angleExtent -= deg2rad(360);
            }

            //拼接ID
            HalconCpp::HTuple hmodelIDs;
            hmodelIDs.Clear();
            for (size_t i = 0; i < models.size(); i++)
            {
                Hlong handle = models[i]->m_nccModel.GetHandle();
                if (handle == 0)
                {
                    continue;
                }
                hmodelIDs.Append(handle);
            }

            HalconCpp::HTuple hrow;
            HalconCpp::HTuple hcolumn;
            HalconCpp::HTuple hangle;
            HalconCpp::HTuple hscore;
            HalconCpp::HTuple hmodel;
            HalconCpp::FindNccModels(himage, hmodelIDs, matchParam.angleStart, angleExtent, matchParam.minScore, matchParam.numMatches, matchParam.maxOverlap, "true", 0, &hrow, &hcolumn, &hangle, &hscore, &hmodel);
            for (int i = 0; i < (int)hrow.Length(); i++)
            {
                MatchResult result;
                result.x = hcolumn[i].D();
                result.y = hrow[i].D();
                result.angle = -hangle[i].D() + matchParam.angle;
                result.score = hscore[i].D();
                result.modelIdentifier = std::to_string(hmodelIDs[hmodel[i].L()].H().GetHandle());
                results.push_back(result);
            }

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

#pragma endregion

#pragma region 参数配置

    double HNccModel::angleStart() const
    {

        return matchParam.angleStart;
    }

    void HNccModel::setAngleStart(double value)
    {
        matchParam.angleStart = value;
    }

    double HNccModel::angleEnd() const
    {

        return matchParam.angleEnd;
    }

    void HNccModel::setAngleEnd(double value)
    {
        matchParam.angleEnd = value;

    }

    double HNccModel::minScore() const
    {

        return matchParam.minScore;
    }

    void HNccModel::setMinScore(double value)
    {
        matchParam.minScore = value;

    }

    int HNccModel::numMatches() const
    {

        return matchParam.numMatches;
    }

    void HNccModel::setNumMatches(int value)
    {
        matchParam.numMatches = value;

    }

    double HNccModel::maxOverlap() const
    {

        return matchParam.maxOverlap;
    }

    void HNccModel::setMaxOverlap(double value)
    {
        matchParam.maxOverlap = value;

    }

    void HNccModel::getOrigin(cv::Point2d& originOffset, double& angle) const
    {
        angle = matchParam.angle;
    }

    void HNccModel::setOrigin(const cv::Point2d& originOffset, double angle)
    {
        matchParam.angle = angle;
    }

#pragma endregion

#pragma region 模板参数

    bool HNccModel::isCreated() const
    {

        return m_nccModel.GetHandle() != 0;
    }

    ScalingMode HNccModel::scalingMode() const
    {
        return m_scalingMode;
    }

    IsotropicScaling HNccModel::isotropicScaling() const
    {
        return m_isotropicScaling;
    }

    AnisotropicScaling HNccModel::anisotropicScaling() const
    {
        return m_anisotropicScaling;
    }

    ReMat HNccModel::templImage() const
    {
        return m_image;
    }

    Region HNccModel::templRegion() const
    {
        return m_region;
    }

#pragma endregion
}
