#include "node.h"
#include <zbar.h>  
#include <opencv2/opencv.hpp>
#include <VisionFlow/timer.h>

using namespace qv;

DataCodeNode::DataCodeNode(void* _parent) : NodeBase(_parent)
{
    name = "DataCodeNode";
    description = "DataCodeNode";
    nodeID = 500001;

    inputs.push_back(referPose);
    inputs.push_back(inputImage);
    outputs.push_back(outputPoses);
    outputs.push_back(outputCodes);

    try
    {
        m_weChatQRCode = new cv::wechat_qrcode::WeChatQRCode("data/qrcode_data/detect.prototxt",
            "data/qrcode_data/detect.caffemodel",
            "data/qrcode_data/sr.prototxt",
            "data/qrcode_data/sr.caffemodel");
    }
    catch (const std::exception&)
    {
        //记录错误
    }

}

RunStatus DataCodeNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
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
        resultCodes.clear();
        resultPoses.clear();
        switch (dataCodeType)
        {
        case qv::DataCodeType::QRCode:
        {
            std::vector<cv::Mat> points;
            resultCodes = cv2zBar(image.getMat(), points);

            //如果zbar识别失败,则用wechat算法来识别,后者耗时更长效果更好
            if (resultCodes.size() == 0)
            {
                if (m_weChatQRCode != nullptr)
                {
                    resultCodes = m_weChatQRCode->detectAndDecode(image.getMat(), points);
                }
            }

            runResult.isOk = resultCodes.size() > 0;
            for (size_t i = 0; i < resultCodes.size(); i++)
            {
                float centerX = (points[i].at<float>(0, 0) + points[i].at<float>(1, 0) + points[i].at<float>(2, 0) + points[i].at<float>(3, 0)) / 4.0f;
                float centerY = (points[i].at<float>(0, 1) + points[i].at<float>(1, 1) + points[i].at<float>(2, 1) + points[i].at<float>(3, 1)) / 4.0f;

                resultPoses.push_back(rv::Pose<double>(centerX, centerY, 0));
            }
            break;
        }
        case qv::DataCodeType::DMCode:

            break;
        case qv::DataCodeType::PDF417:
            break;
        default:
            break;
        }

        //保存参数
        Variant* outputVariant1 = getOutputSource(outputPoses);
        if (outputVariant1 != nullptr)
        {
            outputVariant1->setValue(resultPoses);
        }
        Variant* outputVariant2 = getOutputSource(outputCodes);
        if (outputVariant2 != nullptr)
        {
            outputVariant2->setValue(resultCodes);
        }

        //设置显示图像
        if (rewindow != nullptr)
        {
            for (size_t i = 0; i < resultPoses.size(); i++)
            {
                rewindow->dispCircle(rv::Circle<double>(resultPoses[i].center.x, resultPoses[i].center.y, 10));
            }
        }
        
        runResult.message = (resultCodes.size() > 0) ? resultCodes[0].c_str() : u8"Empty";
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

void qv::DataCodeNode::dispose()
{
    if (m_weChatQRCode != nullptr)
    {
        delete m_weChatQRCode;
        m_weChatQRCode = nullptr;
    }

    NodeBase::dispose();
}

std::vector<std::string> qv::DataCodeNode::cv2zBar(cv::InputArray image, std::vector<cv::Mat>& points)
{
    std::vector<std::string> results;
    points.clear();

    int width = image.cols();
    int height = image.rows();
    uchar* raw = (uchar*)image.getMat().data;
    zbar::Image imageZbar(width, height, "Y800", raw, width * height);

    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    scanner.scan(imageZbar);    //扫描条码    

    for (zbar::Image::SymbolIterator symbol = imageZbar.symbol_begin(); symbol != imageZbar.symbol_end(); ++symbol)
    {
        results.push_back(symbol->get_data());

        cv::Mat point = cv::Mat::zeros(symbol->get_location_size(), 2, CV_32F);

        // Obtain location 
        for (int i = 0; i < symbol->get_location_size(); i++)
        {
            point.at<float>(i, 0) = (float)symbol->get_location_x(i);
            point.at<float>(i, 1) = (float)symbol->get_location_y(i);

        }

        points.push_back(point);
    }

    imageZbar.set_data(NULL, 0);

    return results;
}
