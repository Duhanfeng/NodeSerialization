#include "node.h"
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

FindRectNode::FindRectNode(void* _parent) : NodeBase(_parent)
{
    name = "FindRectNode";
    description = u8"查找矩形";
    nodeID = 400004;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputRect);

    IPreprocess = rv::IPreprocess::create();

}

std::string qv::FindRectNode::className() const
{
    return "FindRect";
}

std::string qv::FindRectNode::displayName() const
{
    return u8"矩形查找";
}

RunStatus FindRectNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
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

void qv::FindRectNode::setRectMix(const rv::RectMix& _rectMix)
{
}

void qv::FindRectNode::updateRectMix()
{
}
