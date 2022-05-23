#include "genericShapeModel.h"
#include <rmath.h>

namespace rv
{
#pragma region 基本控制

    bool GenericShapeModel::create(InputReMat image, InputRegion region)
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
            m_shapeModel.CreateGenericShapeModel();
            m_shapeModel.TrainGenericShapeModel(himage);

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    bool GenericShapeModel::create(InputReMat image, InputRegion region, const IsotropicScaling& scaling)
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
            m_scalingMode = ScalingMode::Isotropic;
            m_isotropicScaling = scaling;
            m_anisotropicScaling = AnisotropicScaling();

            m_shapeModel.Clear();
            m_shapeModel.CreateGenericShapeModel();
            m_shapeModel.SetGenericShapeModelParam("iso_scale_min", scaling.min);
            m_shapeModel.SetGenericShapeModelParam("iso_scale_max", scaling.max);
            m_shapeModel.TrainGenericShapeModel(himage);

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    bool GenericShapeModel::create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling)
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
            m_scalingMode = ScalingMode::Anisotropic;
            m_isotropicScaling = IsotropicScaling();
            m_anisotropicScaling = scaling;

            m_shapeModel.Clear();
            m_shapeModel.CreateGenericShapeModel();
            m_shapeModel.SetGenericShapeModelParam("scale_row_min", scaling.rowMin);
            m_shapeModel.SetGenericShapeModelParam("scale_row_max", scaling.rowMax);
            m_shapeModel.SetGenericShapeModelParam("scale_column_min", scaling.colMin);
            m_shapeModel.SetGenericShapeModelParam("scale_column_max", scaling.colMax);
            m_shapeModel.TrainGenericShapeModel(himage);

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    void GenericShapeModel::clear()
    {
        m_shapeModel.Clear();

    }

    bool GenericShapeModel::find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const
    {
        results.clear();

        if ((m_shapeModel.GetHandle() == 0) || (!isCreated()))
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

            Hlong matchNumber;
            HalconCpp::HGenericShapeModelResult genericResults = m_shapeModel.FindGenericShapeModel(himage, &matchNumber);

            //拼装数据
            if (matchNumber > 0)
            {
                HalconCpp::HTuple columns = genericResults.GetGenericShapeModelResult("all", "column");
                HalconCpp::HTuple rows = genericResults.GetGenericShapeModelResult("all", "row");
                HalconCpp::HTuple angles = genericResults.GetGenericShapeModelResult("all", "angle");
                HalconCpp::HTuple scores = genericResults.GetGenericShapeModelResult("all", "score");
                HalconCpp::HTuple scale_rows = genericResults.GetGenericShapeModelResult("all", "scale_row");
                HalconCpp::HTuple scale_columns = genericResults.GetGenericShapeModelResult("all", "scale_column");
                HalconCpp::HTuple model_identifiers = genericResults.GetGenericShapeModelResult("all", "model_identifier");
                for (Hlong i = 0; i < matchNumber; i++)
                {
                    results.push_back(MatchResult{ columns[i].D(), rows[i].D(), -angles[i].D() + m_angleOffset, scores[i].D(), scale_columns[i].D(), scale_rows[i].D(), (const char*)model_identifiers.ToString() });
                }
            }

            return true;
        }
        catch (const HalconCpp::HOperatorException&)
        {
        }

        return false;
    }

    void GenericShapeModel::getContour(std::vector<cv::Point2d>& points) const
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

    bool GenericShapeModel::find(InputReMat image, InputRegion region, const std::vector<const GenericShapeModel*>& models, std::vector<MatchResult>& results)
    {
        results.clear();

        if (results.size() == 1)
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

            //拼装ID
            HalconCpp::HShapeModel modelArray[64];
            size_t idCount = std::min<size_t>(models.size(), 64);
            for (size_t i = 0; i < idCount; i++)
            {
                modelArray[i] = models[i]->m_shapeModel;
            }
            HalconCpp::HShapeModelArray modelIDArray(modelArray, idCount);

            //匹配
            Hlong matchNumber;
            HalconCpp::HGenericShapeModelResult genericResults = HalconCpp::HShapeModel::FindGenericShapeModel(himage, modelIDArray, &matchNumber);

            //拼装数据
            if (matchNumber > 0)
            {
                HalconCpp::HTuple columns = genericResults.GetGenericShapeModelResult("all", "column");
                HalconCpp::HTuple rows = genericResults.GetGenericShapeModelResult("all", "row");
                HalconCpp::HTuple angles = genericResults.GetGenericShapeModelResult("all", "angle");
                HalconCpp::HTuple scores = genericResults.GetGenericShapeModelResult("all", "score");
                HalconCpp::HTuple scale_rows = genericResults.GetGenericShapeModelResult("all", "scale_row");
                HalconCpp::HTuple scale_columns = genericResults.GetGenericShapeModelResult("all", "scale_column");
                HalconCpp::HTuple model_identifiers = genericResults.GetGenericShapeModelResult("all", "model_identifier");
                for (Hlong i = 0; i < matchNumber; i++)
                {
                    results.push_back(MatchResult{ columns[i].D(),rows[i].D(), angles[i].D(),scores[i].D(), scale_columns[i].D(), scale_rows[i].D() , (const char*)model_identifiers.ToString() });
                }
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

    double GenericShapeModel::angleStart() const
    {

        return m_shapeModel.GetGenericShapeModelParam("angle_start").D();
    }

    void GenericShapeModel::setAngleStart(double value)
    {
        m_shapeModel.SetGenericShapeModelParam("angle_start", value);
    }

    double GenericShapeModel::angleEnd() const
    {

        return m_shapeModel.GetGenericShapeModelParam("angle_end").D();
    }

    void GenericShapeModel::setAngleEnd(double value)
    {
        m_shapeModel.SetGenericShapeModelParam("angle_end", value);
    }

    double GenericShapeModel::minScore() const
    {

        return m_shapeModel.GetGenericShapeModelParam("min_score").D();
    }

    void GenericShapeModel::setMinScore(double value)
    {
        m_shapeModel.SetGenericShapeModelParam("min_score", value);
    }

    int GenericShapeModel::numMatches() const
    {
        HalconCpp::HTuple numTuple = m_shapeModel.GetGenericShapeModelParam("num_matches");

        if (numTuple.Type() == HalconCpp::HTupleType::eTupleTypeString)
        {
            //如果为0,会返回"all"
            return 0;
        }
        else if (numTuple.Type() == HalconCpp::HTupleType::eTupleTypeLong)
        {
            return (int)numTuple.L();
        }

        return 0;
    }

    void GenericShapeModel::setNumMatches(int value)
    {
        m_shapeModel.SetGenericShapeModelParam("num_matches", value);
    }

    double GenericShapeModel::maxOverlap() const
    {

        return m_shapeModel.GetGenericShapeModelParam("max_overlap").D();
    }

    void GenericShapeModel::setMaxOverlap(double value)
    {
        m_shapeModel.SetGenericShapeModelParam("max_overlap", value);
    }

    void GenericShapeModel::getOrigin(cv::Point2d& originOffset, double& angle) const
    {
        angle = m_angleOffset;
    }

    void GenericShapeModel::setOrigin(const cv::Point2d& originOffset, double angle)
    {
        m_angleOffset = angle;
    }

#pragma endregion

#pragma region 模板参数

    bool GenericShapeModel::isCreated() const
    {
        HalconCpp::HTuple stateTuple = m_shapeModel.GetGenericShapeModelParam("needs_training");
        if (stateTuple.Type() == HalconCpp::HTupleType::eTupleTypeString)
        {
            return (stateTuple.ToString() == HalconCpp::HString("\"false\""));  //备注:一定要加转义双引号!!!!!!(草泥马!)
        }

        return false;
    }

    ScalingMode GenericShapeModel::scalingMode() const
    {
        return m_scalingMode;
    }

    IsotropicScaling GenericShapeModel::isotropicScaling() const
    {
        return m_isotropicScaling;
    }

    AnisotropicScaling GenericShapeModel::anisotropicScaling() const
    {
        return m_anisotropicScaling;
    }

    ReMat GenericShapeModel::templImage() const
    {
        return m_image;
    }

    Region GenericShapeModel::templRegion() const
    {
        return m_region;
    }

#pragma endregion
}
