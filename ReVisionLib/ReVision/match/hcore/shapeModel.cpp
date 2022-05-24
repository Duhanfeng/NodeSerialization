#include "shapeModel.h"
#include "ReVision/rmath.h"

namespace rv
{
#pragma region 基本控制

    bool HShapeModel::create(InputReMat image, InputRegion region)
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

            m_shapeModel.Clear();
            m_shapeModel.CreateShapeModel(himage, "auto", -0.39, 6.29, "auto", "auto", "use_polarity", "auto", "auto");

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    bool HShapeModel::create(InputReMat image, InputRegion region, const IsotropicScaling& scaling)
    {

        return create(image, region);
    }

    bool HShapeModel::create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling)
    {

        return create(image, region);
    }

    void HShapeModel::clear()
    {
        m_shapeModel.Clear();

    }

    bool HShapeModel::find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const
    {
        results.clear();

        if (m_shapeModel.GetHandle() == 0)
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
            m_shapeModel.FindShapeModel(himage, matchParam.angleStart, angleExtent, matchParam.minScore, matchParam.numMatches, matchParam.maxOverlap, "least_squares", 0, 0.75, &hrow, &hcolumn, &hangle, &hscore);

            for (int i = 0; i < (int)hrow.Length(); i++)
            {
                MatchResult result;
                result.x = hcolumn[i].D();
                result.y = hrow[i].D();
                result.angle = -hangle[i].D() + matchParam.angle;
                result.score = hscore[i].D();
                result.modelIdentifier = std::to_string(m_shapeModel.GetHandle());
                results.push_back(result);
            }

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    void HShapeModel::getContour(std::vector<cv::Point2d>& points) const
    {
        points.clear();

        //提取轮廓
        HalconCpp::HXLDCont xld = m_shapeModel.GetShapeModelContours(1);
        Hlong count = xld.CountObj();

        //拼接数据
        for (Hlong i = 1; i <= count; i++)
        {
            //获取轮廓组
            HalconCpp::HXLDCont subXld = xld.SelectObj(i);

            //提取点位
            HalconCpp::HTuple rows;
            HalconCpp::HTuple cols;
            subXld.GetContourXld(&rows, &cols);

            for (Hlong j = 0; j < rows.Length(); j++)
            {
                points.push_back(cv::Point2d(cols[j].D(), rows[j].D()));
            }
        }
    }

    bool HShapeModel::find(InputReMat image, InputRegion region, const std::vector<const HShapeModel*>& models, std::vector<MatchResult>& results)
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
                Hlong handle = models[i]->m_shapeModel.GetHandle();
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

    double HShapeModel::angleStart() const
    {

        return matchParam.angleStart;
    }

    void HShapeModel::setAngleStart(double value)
    {
        matchParam.angleStart = value;
    }

    double HShapeModel::angleEnd() const
    {

        return matchParam.angleEnd;
    }

    void HShapeModel::setAngleEnd(double value)
    {
        matchParam.angleEnd = value;

    }

    double HShapeModel::minScore() const
    {

        return matchParam.minScore;
    }

    void HShapeModel::setMinScore(double value)
    {
        matchParam.minScore = value;

    }

    int HShapeModel::numMatches() const
    {

        return matchParam.numMatches;
    }

    void HShapeModel::setNumMatches(int value)
    {
        matchParam.numMatches = value;

    }

    double HShapeModel::maxOverlap() const
    {

        return matchParam.maxOverlap;
    }

    void HShapeModel::setMaxOverlap(double value)
    {
        matchParam.maxOverlap = value;

    }

    void HShapeModel::getOrigin(cv::Point2d& originOffset, double& angle) const
    {
        angle = matchParam.angle;
    }

    void HShapeModel::setOrigin(const cv::Point2d& originOffset, double angle)
    {
        matchParam.angle = angle;
    }

#pragma endregion

#pragma region 模板参数

    bool HShapeModel::isCreated() const
    {

        return m_shapeModel.GetHandle() != 0;
    }

    ScalingMode HShapeModel::scalingMode() const
    {
        return m_scalingMode;
    }

    IsotropicScaling HShapeModel::isotropicScaling() const
    {
        return m_isotropicScaling;
    }

    AnisotropicScaling HShapeModel::anisotropicScaling() const
    {
        return m_anisotropicScaling;
    }

    ReMat HShapeModel::templImage() const
    {
        return m_image;
    }

    Region HShapeModel::templRegion() const
    {
        return m_region;
    }

#pragma endregion
}
