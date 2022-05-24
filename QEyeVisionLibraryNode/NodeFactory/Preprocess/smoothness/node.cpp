#include "node.h"
#include <opencv2/opencv.hpp>

using namespace qv;

SmoothnessNode::SmoothnessNode(void* _parent) : NodeBase(_parent)
{
    name = "SmoothnessNode";
    description = u8"平滑";
    nodeID = 100002;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputImage);

    IPreprocess = rv::IPreprocess::create();

}

std::string qv::SmoothnessNode::className() const
{
    return "Smoothness";
}

std::string qv::SmoothnessNode::displayName() const
{
    return u8"图像平滑";
}

RunStatus SmoothnessNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }

        if ((kernelSize == 0) || (kernelSize % 2) != 1)
        {
            throw std::invalid_argument("kernel 必须大于零且为奇数");
        }

        //处理
        rv::ReMat dst;
        switch (method)
        {
        case qv::SmoothnessMethod::MeanFilter:
            IPreprocess->meanImage(image, dst, kernelSize);
            break;
        case qv::SmoothnessMethod::MedianFilter:
            IPreprocess->medianImage(image, dst, kernelSize);
            break;
        case qv::SmoothnessMethod::GaussianFilter:
            IPreprocess->gaussImage(image, dst, kernelSize);
            break;
        default:
            break;
        }
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
