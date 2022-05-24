#include "imgproc.h"
#include "ReVision/rmath.h"

namespace rv
{
    void rv::ImageProc::clipImage(InputReMat src, OutputReMat dst, InputRegion region)
    {
        if (src.empty())
        {
            return;
        }
        cv::RotatedRect rect = region.toCvRotatedRect();
        if (rect.size.area() < 100)
        {
            return;
        }

        cv::Mat _src = src.getMat();

        //关于角度取反: region相对轴为正方向(顺时针)时,图像应当为相对轴为负进行旋转
        double angle = -deg2rad(rect.angle);

        //计算平移矩阵1
        cv::Mat translationMat1 = cv::Mat::eye(3, 3, CV_32F);
        translationMat1.at<float>(0, 2) = -rect.center.x;
        translationMat1.at<float>(1, 2) = -rect.center.y;

        //计算平移矩阵2
        cv::Mat translationMat2 = cv::Mat::eye(3, 3, CV_32F);
        translationMat2.at<float>(0, 2) = rect.size.width / 2.0f;
        translationMat2.at<float>(1, 2) = rect.size.height / 2.0f;

        //计算旋转矩阵
        float sinValue = float(std::sin(angle));
        float cosValue = float(std::cos(angle));
        cv::Mat rotationMat = cv::Mat::eye(3, 3, CV_32F);
        rotationMat.at<float>(0, 0) = cosValue;
        rotationMat.at<float>(0, 1) = -sinValue;
        rotationMat.at<float>(1, 0) = sinValue;
        rotationMat.at<float>(1, 1) = cosValue;

        //计算综合矩阵
        //1.先将旋转中心平移到原点
        //2.围绕旋转中心旋转
        //3.图像平移到新的尺寸边界
        cv::Mat mat = translationMat2 * (rotationMat * translationMat1);

        //warpAffine所需要的矩阵为2x3的(最后一行的0 0 1去掉),转换格式
        cv::Mat affineMat(cv::Size(3, 2), CV_32F);
        affineMat.at<float>(0, 0) = mat.at<float>(0, 0);
        affineMat.at<float>(0, 1) = mat.at<float>(0, 1);
        affineMat.at<float>(0, 2) = mat.at<float>(0, 2);
        affineMat.at<float>(1, 0) = mat.at<float>(1, 0);
        affineMat.at<float>(1, 1) = mat.at<float>(1, 1);
        affineMat.at<float>(1, 2) = mat.at<float>(1, 2);

        //对图像进行旋转(BORDER_REPLICATE的边界外推方式)
        cv::Mat _dst;
        warpAffine(_src, _dst, affineMat, rect.size, cv::INTER_LINEAR, cv::BORDER_REPLICATE);

        dst = ReMat(_dst);
    }

    void rv::ImageProc::skeleton(InputReMat src, OutputReMat dst)
    {
        if (src.empty())
        {
            return;
        }

        cv::Mat _dst = src.getMat().clone();
        std::vector<cv::Point> deleteList;

        int height = _dst.rows;
        int width = _dst.cols;
        bool inOddIterations = true;
        std::mutex mt;

        while (true)
        {
            cv::parallel_for_(cv::Range(1, height - 1), [&](const cv::Range& range)
                {
                    for (int r = range.start; r < range.end; r++) //这是需要并行计算的for循环
                    {
                        uchar* data_last = _dst.ptr<uchar>(r - 1);
                        uchar* data = _dst.ptr<uchar>(r);
                        uchar* data_next = _dst.ptr<uchar>(r + 1);

                        for (int c = 1; c < (width - 1); c++)
                        {
                            int neighbourhood[9] = { 0 };
                            if (data[c])
                            {
                                int whitePointCount = 0;
                                neighbourhood[0] = 1;

                                if (data_last[c]) neighbourhood[1] = 1;
                                if (data_last[c + 1]) neighbourhood[2] = 1;
                                if (data[c + 1]) neighbourhood[3] = 1;
                                if (data_next[c + 1]) neighbourhood[4] = 1;
                                if (data_next[c]) neighbourhood[5] = 1;
                                if (data_next[c - 1]) neighbourhood[6] = 1;
                                if (data[c - 1]) neighbourhood[7] = 1;
                                if (data_last[c - 1]) neighbourhood[8] = 1;

                                for (int k = 1; k < 9; k++)
                                {
                                    whitePointCount += neighbourhood[k];
                                }

                                if ((whitePointCount >= 2) && (whitePointCount <= 6))
                                {
                                    int ap = 0;
                                    if ((neighbourhood[1] == 0) && (neighbourhood[2] == 1)) ap++;
                                    if ((neighbourhood[2] == 0) && (neighbourhood[3] == 1)) ap++;
                                    if ((neighbourhood[3] == 0) && (neighbourhood[4] == 1)) ap++;
                                    if ((neighbourhood[4] == 0) && (neighbourhood[5] == 1)) ap++;
                                    if ((neighbourhood[5] == 0) && (neighbourhood[6] == 1)) ap++;
                                    if ((neighbourhood[6] == 0) && (neighbourhood[7] == 1)) ap++;
                                    if ((neighbourhood[7] == 0) && (neighbourhood[8] == 1)) ap++;
                                    if ((neighbourhood[8] == 0) && (neighbourhood[1] == 1)) ap++;

                                    if (ap == 1)
                                    {
                                        if (inOddIterations && (neighbourhood[3] * neighbourhood[5] * neighbourhood[7] == 0)
                                            && (neighbourhood[1] * neighbourhood[3] * neighbourhood[5] == 0))
                                        {
                                            mt.lock();
                                            deleteList.push_back(cv::Point(c, r));
                                            mt.unlock();
                                        }
                                        else if (!inOddIterations && (neighbourhood[1] * neighbourhood[5] * neighbourhood[7] == 0)
                                            && (neighbourhood[1] * neighbourhood[3] * neighbourhood[7] == 0))
                                        {
                                            mt.lock();
                                            deleteList.push_back(cv::Point(c, r));
                                            mt.unlock();
                                        }
                                    }
                                }
                            }
                        }

                    }
                });

            int count = (int)deleteList.size();
            if (count == 0)
            {
                break;
            }

            cv::parallel_for_(cv::Range(0, count), [&](const cv::Range& range)
                {
                    for (int i = range.start; i < range.end; i++) //这是需要并行计算的for循环
                    {
                        _dst.ptr<uchar>(deleteList[i].y)[deleteList[i].x] = 0;
                    }
                });

            deleteList.clear();

            inOddIterations = !inOddIterations;

        }

        //以上细化操作的仍然会有一些重叠边缘存在,完全过滤无效点位
        //此步骤不适合以并行方式执行
        for (int r = 1; r < height - 1; r++)
        {
            uchar* data_last = _dst.ptr<uchar>(r - 1);
            uchar* data = _dst.ptr<uchar>(r);
            uchar* data_next = _dst.ptr<uchar>(r + 1);

            for (int c = 1; c < width - 1; c++)
            {
                if ((data[c] > 0) &&
                    ((data[c - 1] > 0) || (data[c + 1] > 0)) &&
                    ((data_last[c] > 0) || (data_next[c] > 0)))
                {
                    data[c] = 0;
                }
            }
        }

        dst = ReMat(_dst);
    }

    void rv::ImageProc::connection(InputReMat src, std::vector<ReMat>& regions)
    {
        regions.clear();
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();

        //轮廓分析
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(_src, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

        //获取轮廓图
        for (size_t i = 0; i < contours.size(); i++)
        {
            cv::Mat region = cv::Mat::zeros(_src.size(), CV_8UC1);
            drawContours(region, contours, (int)i, cv::Scalar(255, 255, 255), -1);
            regions.push_back(region);
        }
    }

    void rv::ImageProc::buildPyramid(InputReMat src, std::vector<ReMat>& dst, int maxlevel)
    {
        dst.clear();
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();

        cv::Mat _dst = _src;
        dst.push_back(_dst.clone());

        for (int i = 1; i <= maxlevel; i++)
        {
            if ((_dst.size().width > 1) && (_dst.size().height > 1))
            {
                cv::resize(_dst, _dst, {}, 0.5, 0.5, cv::INTER_AREA);
                dst.push_back(_dst.clone());
            }
            else
            {
                dst.push_back(cv::Mat());
            }
        }

    }

    void rv::ImageProc::canny(InputReMat src, OutputReMat dst, int threshold1, int threshold2)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::Canny(_src, _dst, threshold1, threshold2);
        dst = ReMat(_dst);
    }

    void rv::ImageProc::sobel(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy, int ksize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::Sobel(_src, _dst, ddepth, dx, dy, ksize);
        dst = ReMat(_dst);
    }

    void rv::ImageProc::scharr(InputReMat src, OutputReMat dst, int ddepth, int dx, int dy)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::Scharr(_src, _dst, ddepth, dx, dy);
        dst = ReMat(_dst);
    }

    void rv::ImageProc::laplacian(InputReMat src, OutputReMat dst, int ddepth, int ksize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dst;
        cv::Laplacian(_src, _dst, ddepth, ksize);
        dst = ReMat(_dst);
    }

    void rv::ImageProc::spatialGradient(InputReMat src, OutputReMat dx, OutputReMat dy, int ksize)
    {
        if (src.empty())
        {
            return;
        }
        cv::Mat _src = src.getMat();
        cv::Mat _dx, _dy;
        cv::spatialGradient(_src, _dx, _dy, ksize);
        dx = ReMat(_dx);
        dy = ReMat(_dy);
    }

}
