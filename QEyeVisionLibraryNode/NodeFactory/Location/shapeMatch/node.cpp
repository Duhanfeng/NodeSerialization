#include "node.h"
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

ShapeMatchNode::ShapeMatchNode(void* _parent) : NodeBase(_parent)
{
    name = "ShapeMatchNode";
    description = u8"形状匹配";
    nodeID = 200001;

    inputs.push_back(referPose);
    inputs.push_back(inputImage);
    outputs.push_back(outputPoses);
    outputs.push_back(outputScores);

}

std::string qv::ShapeMatchNode::className() const
{
    return "ShapeMatch";
}

std::string qv::ShapeMatchNode::displayName() const
{
    return u8"轮廓匹配";
}

RunStatus ShapeMatchNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }

        if (rewindow != nullptr)
        {
            rewindow->setGraphicsStyle(rv::GraphicsStyle::Simple);
            rewindow->setDrawStyle(rv::DrawStyle::Margin);
            rewindow->setLineWidth(1);
        }

        //匹配
        if (matchModel.isCreated())
        {
            resultPoses.clear();
            resultScores.clear();

            Variant* refVariant = getInputSource(referPose);
            if (isEnableRefer && (refVariant != nullptr))
            {
                //获取当前的参考坐标
                const std::vector<rv::Pose<double>>& poses = refVariant->getPoseArray();

                for (size_t i = 0; i < (onlyReferFirst ? std::min<size_t>(1, poses.size()) : poses.size()); i++)
                {
                    rv::Region newRegion = affineTransRegion(poses[i]);

                    std::vector<rv::MatchResult> results;
                    matchModel.find(image, newRegion, results);
                    for (size_t i = 0; i < results.size(); i++)
                    {
                        resultPoses.push_back(rv::Pose<double>(results[i].x, results[i].y, results[i].angle));
                        resultScores.push_back(results[i].score);
                    }

                    //设置region区域
                    if (!newRegion.empty() && newRegion.isShapeRetatedRect())
                    {
                        cv::RotatedRect rect = newRegion.toCvRotatedRect();

                        //设置显示图像
                        if (rewindow != nullptr)
                        {
                            rewindow->dispRotatedRect(rv::RotatedRect<double>(rect.center.x, rect.center.y, rect.size.width, rect.size.height, rv::deg2rad(rect.angle)));
                        }
                    }
                }
            }
            else
            {
                std::vector<rv::MatchResult> results;
                matchModel.find(image, region, results);
                for (size_t i = 0; i < results.size(); i++)
                {
                    resultPoses.push_back(rv::Pose<double>(results[i].x, results[i].y, results[i].angle));
                    resultScores.push_back(results[i].score);
                }

                //设置region区域
                if (!region.empty() && region.isShapeRetatedRect())
                {
                    cv::RotatedRect rect = region.toCvRotatedRect();

                    //设置显示图像
                    if (rewindow != nullptr)
                    {
                        rewindow->dispRotatedRect(rv::RotatedRect<double>(rect.center.x, rect.center.y, rect.size.width, rect.size.height, rv::deg2rad(rect.angle)));
                    }
                }
            }

            runResult.isOk = resultScores.size() > 0;

            //保存参数
            Variant* outputVariant = getOutputSource(outputPoses);
            if (outputVariant != nullptr)
            {
                outputVariant->setValue(resultPoses);
            }
            Variant* outputVariant2 = getOutputSource(outputScores);
            if (outputVariant2 != nullptr)
            {
                outputVariant2->setValue(resultScores);
            }
        }

        //设置显示图像
        if (matchModel.isCreated())
        {
            //设置显示图像
            if (rewindow != nullptr)
            {
                for (size_t i = 0; i < resultPoses.size(); i++)
                {
                    rewindow->dispCircle(rv::Circle<double>(resultPoses[i].center.x, resultPoses[i].center.y, 10));
                }
            }

            runResult.message = std::to_string(resultPoses.size());
            for (size_t i = 0; i < resultPoses.size(); i++)
            {
                char mesBuff[512] = { 0 };
                sprintf(mesBuff, ":%.2f,%.2f,%.2f,%0.2f", resultPoses[i].center.x, resultPoses[i].center.y, rv::rad2deg(resultPoses[i].angle), resultScores[i]);
                runResult.message += mesBuff;
            }
        }
        else
        {
            runResult.message = u8"模板无效";
        }
        
        runResult.result = RunResult::Accept;
    }
    catch (const std::exception& ex)
    {
        runResult.message = std::string(ex.what());
        runResult.result = RunResult::Error;
    }
    runResult.totalTime = totalTimer.elapsed() * 1000.0;

    return runResult;
}

#pragma region 模板操作

bool qv::ShapeMatchNode::createTempl(rv::InputReMat image, rv::InputRegion region)
{
    
    return matchModel.create(image, region);
}

bool qv::ShapeMatchNode::getTemplImage(rv::OutputReMat image)
{
    if (!matchModel.isCreated())
    {
        return false;
    }

    //获取原图
    cv::Mat showImage = matchModel.templImage().getMat().clone();
    if (showImage.channels() == 1)
    {
        cv::cvtColor(showImage, showImage, cv::COLOR_GRAY2BGR);
    }

    //获取点位
    std::vector<cv::Point2d> points;
    matchModel.getContour(points);

    if (matchModel.templRegion().isShapeRetatedRect())
    {
        cv::RotatedRect rect = matchModel.templRegion().toCvRotatedRect();
        //描点
        for (size_t i = 0; i < points.size(); i++)
        {
            cv::circle(showImage, { int(points[i].x + rect.center.x), int(points[i].y + rect.center.y) }, 0, { 0, 255, 0 }, -1);
        }

        //裁剪
        rv::ReMat dst;
        rv::ReMat showReMat(showImage);
        rv::IImageProc::create()->clipImage(showReMat, dst, rect);
        showImage = dst.getMat();
    }

    //if (matchModel.templRegion().type() == rv::Region::RegionType::Roi_Rect2)
    //{
    //    const cv::RotatedRect& rect = matchModel.templRegion().getRectRegion();
    //    //描点
    //    for (size_t i = 0; i < points.size(); i++)
    //    {
    //        cv::circle(showImage, { int(points[i].x + rect.center.x), int(points[i].y + rect.center.y) }, 1, { 0, 255, 0 }, -1);
    //    }
    //    //裁剪
    //    rv::ReMat dst;
    //    rv::ReMat showReMat(showImage);
    //    rv::IImageProc::create()->clipImage(showReMat, dst, rect);
    //    showImage = dst.getMat();
    //}

    image = showImage;

    return !image.empty();
}

bool qv::ShapeMatchNode::isTemplEmpty()
{
    return !matchModel.isCreated();
}

void qv::ShapeMatchNode::recoverTempl()
{
    if (!matchModel.isCreated() && !matchModel.templImage().empty())
    {
        matchModel.create(matchModel.templImage(), matchModel.templRegion());
    }

}

#pragma endregion
