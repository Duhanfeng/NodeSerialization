#include "preprocess.h"

namespace rv
{
    void rv::Preprocess::meanImage(InputReMat src, OutputReMat dst, int kernelSize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::blur(_src, _dst, { kernelSize, kernelSize });
        dst = ReMat(_dst);
    }

    void rv::Preprocess::medianImage(InputReMat src, OutputReMat dst, int kernelSize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::medianBlur(_src, _dst, kernelSize);
        dst = ReMat(_dst);
    }

    void rv::Preprocess::gaussImage(InputReMat src, OutputReMat dst, int kernelSize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::GaussianBlur(_src, _dst, { kernelSize, kernelSize }, 0, 0);
        dst = ReMat(_dst);
    }

    void Preprocess::threshold(cv::InputArray src, cv::OutputArray dst, uchar threshold1, uchar threshold2)
    {
        if (src.channels() != 1)
        {
            return;
        }

        uchar minT = std::min<uchar>(threshold1, threshold2);
        uchar maxT = std::max<uchar>(threshold1, threshold2);

        cv::Mat srcMat = src.getMat();
        cv::Mat dstMat = cv::Mat::zeros(srcMat.rows, srcMat.cols, CV_8U);
        int rows = srcMat.rows;
        int cols = srcMat.cols;

        cv::parallel_for_(cv::Range(0, rows), [&](const cv::Range& range)
            {
                for (int index = range.start; index < range.end; index++) //这是需要并行计算的for循环
                {
                    uchar* srcData = srcMat.ptr<uchar>(index);
                    uchar* dstData = dstMat.ptr<uchar>(index);
                    for (int c = 0; c < cols; c++)
                    {
                        if ((*srcData >= minT) && (*srcData <= maxT))
                        {
                            *dstData = 255;
                        }

                        srcData++;
                        dstData++;
                    }
                }
            });

        if (dst.kind() == cv::_InputArray::MAT)
        {
            dst.assign(dstMat);
        }
    }

    void rv::Preprocess::threshold(InputReMat src, OutputReMat dst, int threshold1, int threshold2)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;

        if (threshold1 == 0)
        {
            cv::threshold(_src, _dst, threshold2, 255, cv::ThresholdTypes::THRESH_BINARY_INV);
        }
        else if (threshold2 == 255)
        {
            cv::threshold(_src, _dst, threshold1, 255, cv::ThresholdTypes::THRESH_BINARY);
        }
        else
        {
            threshold(_src, _dst, threshold1, threshold2);
        }

        dst = ReMat(_dst);
    }

    void rv::Preprocess::morphology(InputReMat src, OutputReMat dst, MorphTypes type, int kernelSize, KernShapes shape)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;

        //创建内核
        cv::Mat kernel;
        switch (shape)
        {
        case rv::IPreprocess::Rectangle:
            kernel = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, { kernelSize, kernelSize });
            break;
        case rv::IPreprocess::Circle:
            kernel = cv::getStructuringElement(cv::MorphShapes::MORPH_ELLIPSE, { kernelSize, kernelSize });
            break;
        default:
            break;
        }

        switch (type)
        {
        case rv::IPreprocess::Dilate:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_DILATE, kernel);
            break;
        case rv::IPreprocess::Erode:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_ERODE, kernel);
            break;
        case rv::IPreprocess::Close:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_CLOSE, kernel);
            break;
        case rv::IPreprocess::Open:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_OPEN, kernel);
            break;
        case rv::IPreprocess::Gradient:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_GRADIENT, kernel);
            break;
        case rv::IPreprocess::TopHat:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_TOPHAT, kernel);
            break;
        case rv::IPreprocess::BlackHat:
            cv::morphologyEx(_src, _dst, cv::MorphTypes::MORPH_BLACKHAT, kernel);
            break;
        default:
            break;
        }

        dst = ReMat(_dst);

    }

    void rv::Preprocess::convertColor(const cv::Point3_<uchar>& src, cv::Point3_<uchar>& dst, ColorConversionCodes code)
    {
        cv::Mat _src(1, 1, CV_8UC3);
        cv::Mat _dst;
        _src.at<cv::Vec3b>(0, 0)[0] = src.x;
        _src.at<cv::Vec3b>(0, 0)[1] = src.y;
        _src.at<cv::Vec3b>(0, 0)[2] = src.z;

        switch (code)
        {
        case rv::IPreprocess::RGB2GRAY:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2GRAY);
            break;
        case rv::IPreprocess::RGB2BGR:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2BGR);
            break;
        case rv::IPreprocess::RGB2HSV:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2HSV);
            break;
        case rv::IPreprocess::RGB2HLS:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2HLS);
            break;
        case rv::IPreprocess::BGR2GRAY:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2GRAY);
            break;
        case rv::IPreprocess::BGR2RGB:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2RGB);
            break;
        case rv::IPreprocess::BGR2HSV:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2HSV);
            break;
        case rv::IPreprocess::BGR2HLS:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2HLS);
            break;
        case rv::IPreprocess::GRAY2RGB:
            cv::cvtColor(_src, _dst, cv::COLOR_GRAY2RGB);
            break;
        case rv::IPreprocess::GRAY2BGR:
            cv::cvtColor(_src, _dst, cv::COLOR_GRAY2BGR);
            break;
        case rv::IPreprocess::HSV2BGR:
            cv::cvtColor(_src, _dst, cv::COLOR_HSV2BGR);
            break;
        case rv::IPreprocess::HSV2RGB:
            cv::cvtColor(_src, _dst, cv::COLOR_HSV2RGB);
            break;
        default:
            break;
        }

        if (!_dst.empty())
        {
            dst.x = _dst.at<cv::Vec3b>(0, 0)[0];
            dst.y = _dst.at<cv::Vec3b>(0, 0)[1];
            dst.z = _dst.at<cv::Vec3b>(0, 0)[2];
        }
    }

    void rv::Preprocess::convertColor(InputReMat src, OutputReMat dst, ColorConversionCodes code)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;

        switch (code)
        {
        case rv::IPreprocess::RGB2GRAY:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2GRAY);
            break;
        case rv::IPreprocess::RGB2BGR:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2BGR);
            break;
        case rv::IPreprocess::RGB2HSV:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2HSV);
            break;
        case rv::IPreprocess::RGB2HLS:
            cv::cvtColor(_src, _dst, cv::COLOR_RGB2HLS);
            break;
        case rv::IPreprocess::BGR2GRAY:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2GRAY);
            break;
        case rv::IPreprocess::BGR2RGB:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2RGB);
            break;
        case rv::IPreprocess::BGR2HSV:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2HSV);
            break;
        case rv::IPreprocess::BGR2HLS:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2HLS);
            break;
        case rv::IPreprocess::GRAY2RGB:
            cv::cvtColor(_src, _dst, cv::COLOR_GRAY2RGB);
            break;
        case rv::IPreprocess::GRAY2BGR:
            cv::cvtColor(_src, _dst, cv::COLOR_GRAY2BGR);
            break;
        default:
            break;
        }

        dst = ReMat(_dst);
    }

    void rv::Preprocess::extractColorPlane(InputReMat src, OutputReMat dst, ColorPlanCodes plan)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;

        cv::Mat hsv;
        std::vector<cv::Mat> colorChannels;
        switch (plan)
        {
        case rv::IPreprocess::Gray:
            cv::cvtColor(_src, _dst, cv::COLOR_BGR2GRAY);
            break;
        case rv::IPreprocess::BGR_B:
            cv::split(_src, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[0];
            }
            break;
        case rv::IPreprocess::BGR_G:
            cv::split(_src, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[1];
            }
            break;
        case rv::IPreprocess::BGR_R:
            cv::split(_src, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[2];
            }
            break;
        case rv::IPreprocess::HSV_H:
            cv::cvtColor(_src, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV);
            cv::split(hsv, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[0];
            }
            break;
        case rv::IPreprocess::HSV_S:
            cv::cvtColor(_src, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV);
            cv::split(hsv, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[1];
            }
            break;
        case rv::IPreprocess::HSV_V:
            cv::cvtColor(_src, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV);
            cv::split(hsv, colorChannels);
            if (colorChannels.size() >= 3)
            {
                _dst = colorChannels[2];
            }
            break;
        default:
            break;
        }

        dst = ReMat(_dst);
    }

    void rv::Preprocess::filter2D(InputReMat src, OutputReMat dst, int depth, InputReMat kernel)
    {
        if (src.empty() || kernel.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _kernel = kernel.getMat();
        cv::Mat _dst;
        cv::filter2D(_src, _dst, depth, _kernel);
        dst = ReMat(_dst);
    }

    void rv::Preprocess::lut(InputReMat src, InputReMat lut, OutputReMat dst)
    {
        if (src.empty() || lut.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _lut = lut.getMat();
        cv::Mat _dst;
        cv::LUT(_src, _lut, _dst);
        dst = ReMat(_dst);
    }

    void rv::Preprocess::equalizeHist(InputReMat src, OutputReMat dst)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::equalizeHist(_src, _dst);
        dst = ReMat(_dst);
    }

    void rv::Preprocess::invert(InputReMat src, OutputReMat dst)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst = 255 - _src;
        dst = ReMat(_dst);
    }

    void rv::Preprocess::denoising(InputReMat src, OutputReMat dst)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        if (_src.channels() == 1)
        {
            cv::fastNlMeansDenoising(_src, _dst);
        }
        else
        {
            cv::fastNlMeansDenoisingColored(_src, _dst);
        }
        dst = ReMat(_dst);
    }

}

