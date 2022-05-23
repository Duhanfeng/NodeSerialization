#include "node.h"
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

MorphologyNode::MorphologyNode(void* _parent) : NodeBase(_parent)
{
    name = "MorphologyNode";
    description = u8"形态学";
    nodeID = 100003;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputImage);

    IPreprocess = rv::IPreprocess::create();

}

RunStatus MorphologyNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }

        //处理
        rv::ReMat dst;
        IPreprocess->morphology(image, dst, morphTypes, kernelSize, kernShapes);
        runResult.isOk = true;

        //保存参数
        Variant* outputVariant = getOutputSource(outputImage);
        if (outputVariant != nullptr)
        {
            outputVariant->setValue(dst);
        }

        //设置显示图像
        if (rewindow != nullptr)
        {
            rewindow->dispImage(dst);
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
