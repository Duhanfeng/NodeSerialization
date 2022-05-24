#include "node.h"
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

FindCircleNode::FindCircleNode(void* _parent) : NodeBase(_parent)
{
    name = "FindCircleNode";
    description = u8"查找圆";
    nodeID = 400003;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputCircle);

    IPreprocess = rv::IPreprocess::create();

}

std::string qv::FindCircleNode::className() const
{
    return "FindCircle";
}

std::string qv::FindCircleNode::displayName() const
{
    return u8"圆查找";
}

RunStatus FindCircleNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }


        runResult.isOk = true;

        //保存参数
        //Variant* outputVariant = getOutputSource(outputImage);
        //if (outputVariant != nullptr)
        //{
        //    outputVariant->setValue(dst);
        //}

        //设置显示图像
        if (rewindow != nullptr)
        {
            
        }

        runResult.message = u8"OK";
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

void qv::FindCircleNode::setCircleMix(const rv::RectMix& _rectMix)
{
}

void qv::FindCircleNode::updateCircleMix()
{
}
