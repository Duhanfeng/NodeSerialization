#pragma once

#include <opencv2/opencv.hpp>
#include "hmat.h"

namespace rv
{
    class ReMat
    {
    public:

        //这个数值与GenICam标准中的数值一致
        enum BayerType
        {
            Bayer_GR = 17301512,
            Bayer_RG = 17301513,
            Bayer_GB = 17301514,
            Bayer_BG = 17301515,
        };

    public:
        explicit ReMat();
        explicit ReMat(const std::string& file);
        ReMat(const ReMat& mat, bool copyData = false);
        ReMat(const cv::Mat& mat, bool copyData = false);
        ReMat(cv::InputArray mat, bool copyData = false);
        ReMat(const HMat& mat, bool copyData = false);
        explicit ReMat(int rows, int cols, int channels, void* data, bool copyData = false);
        explicit ReMat(int rows, int cols, void* data, BayerType bayerType);
        ~ReMat();

        ReMat& operator = (const ReMat& mat);
        ReMat& operator = (const cv::Mat& mat);
        ReMat& operator = (const HMat& mat);

        //功能接口
        bool read(const std::string& file);
        void clear();
        ReMat clone() const;
        bool empty() const;
        cv::Mat getMat() const;
        HMat getHMat() const;
        cv::Mat getRChannel() const;
        cv::Mat getGChannel() const;
        cv::Mat getBChannel() const;

        //图像参数
        int rows() const { return m_rows; }
        int cols() const { return m_cols; }
        int step() const { return m_step; }           //单行的长度,step = cols * channels;
        int channels() const { return m_channels; }   //通道数
        cv::Size size() const { return cv::Size(m_cols, m_rows); }

    private:
        //图像信息
        bool m_empty{ true };
        int m_rows{ 0 };
        int m_cols{ 0 };
        int m_step{ 0 };
        int m_channels{ 0 };

        //图像底层实例
        bool m_needMerge = false;   //rgb/bgr图像保存在_r,_g,_b中,但是混合图像_src尚未分配
        bool m_needSplit = false;   //rgb/bgr图像保存在_src之中,但是_r,_g,_b单通道图像尚未分配
        cv::Mat m_cvMat;
        cv::Mat m_r;
        cv::Mat m_g;
        cv::Mat m_b;
        HMat m_hMat;                //在内存由外接托管的情况下,需要一个指向其内存地址的对象,以避免其智能指针的释放;如非必要,不使用这个对象

    private:
        void updateImageInfo();

        void _setData(const cv::Mat& src, bool copyData = false);
        void _setData(const HMat& src, bool copyData = false);
        void _setData(int rows, int cols, int channels, void* data, bool copyData = false);
        void _setData(int rows, int cols, void* data, BayerType bayerType);

        static HMat deepCopy(const HMat& src);

    };

    typedef const ReMat& InputReMat;
    typedef ReMat& OutputReMat;
    typedef OutputReMat InputOutputReMat;
    typedef ReMat& Ref_ReMat;

}