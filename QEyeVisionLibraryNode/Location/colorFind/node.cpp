#include "node.h"
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

namespace
{
    double hsvDistance(uchar h1, uchar s1, uchar v1, uchar h2, uchar s2, uchar v2)
    {


    }
}

ColorFindNode::ColorFindNode(void* _parent) : NodeBase(_parent)
{
    name = "ColorFindNode";
    description = u8"颜色查找";
    nodeID = 200004;

    inputs.push_back(referPose);
    inputs.push_back(inputImage);
    outputs.push_back(outputPoses);
    outputs.push_back(outputScores);

    IPreprocess = rv::IPreprocess::create();

}

RunStatus ColorFindNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }

        //设置显示图像
        if (rewindow != nullptr)
        {

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

void qv::ColorFindNode::hsv2bgr(const cv::Point3_<uchar>& image, cv::Point3_<uchar>& dst)
{
    IPreprocess->convertColor(image, dst, rv::IPreprocess::ColorConversionCodes::HSV2BGR);
}

void qv::ColorFindNode::bgr2hsv(const cv::Point3_<uchar>& image, cv::Point3_<uchar>& dst)
{
    IPreprocess->convertColor(image, dst, rv::IPreprocess::ColorConversionCodes::BGR2HSV);
}
