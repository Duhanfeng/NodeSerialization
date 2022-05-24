#include "remat.h"

#pragma region 构造函数

rv::ReMat::ReMat()
{
}

rv::ReMat::ReMat(const std::string& file)
{
    read(file);

}

rv::ReMat::ReMat(const ReMat& mat, bool copyData)
{
    m_empty = mat.m_empty;
    m_rows = mat.m_rows;
    m_cols = mat.m_cols;
    m_step = mat.m_step;
    m_channels = mat.m_channels;

    if (m_empty)
    {
        return;
    }

    if (copyData)
    {
        if (m_channels == 1)
        {
            //如果是单通道图像,就算mat中的图像内存来自第三方的HMat,本次clone也实现内存的拷贝,所以不需要再管m_hMat
            m_cvMat = mat.m_cvMat.clone();
        }
        else
        {
            if (m_needSplit)
            {
                m_cvMat = mat.m_cvMat.clone();
                m_needSplit = mat.m_needSplit;
            }
            else if (m_needMerge)
            {
                m_r = mat.m_r.clone();
                m_g = mat.m_g.clone();
                m_b = mat.m_b.clone();
                m_needMerge = mat.m_needMerge;
            }
            else
            {
                m_cvMat = mat.m_cvMat.clone();
                m_r = mat.m_r.clone();
                m_g = mat.m_g.clone();
                m_b = mat.m_b.clone();
                m_needSplit = false;
                m_needMerge = false;
            }
        }
    }
    else
    {
        m_needMerge = mat.m_needMerge;
        m_needSplit = mat.m_needSplit;
        m_cvMat = mat.m_cvMat;
        m_r = mat.m_r;
        m_g = mat.m_g;
        m_b = mat.m_b;
        m_hMat = mat.m_hMat;
    }

}

rv::ReMat::ReMat(const cv::Mat& mat, bool copyData)
{
    _setData(mat, copyData);
}

rv::ReMat::ReMat(cv::InputArray mat, bool copyData)
{
    _setData(mat.getMat(), copyData);
}

rv::ReMat::ReMat(const HMat& mat, bool copyData)
{
    _setData(mat, copyData);
}

rv::ReMat::ReMat(int rows, int cols, int channels, void* data, bool copyData)
{
    _setData(rows, cols, channels, data, copyData);
}

rv::ReMat::ReMat(int rows, int cols, void* data, BayerType bayerType)
{
    _setData(rows, cols, data, bayerType);
}

rv::ReMat::~ReMat()
{
    clear();
}

rv::ReMat& rv::ReMat::operator=(const ReMat& mat)
{
    m_empty = mat.m_empty;
    m_rows = mat.m_rows;
    m_cols = mat.m_cols;
    m_step = mat.m_step;
    m_channels = mat.m_channels;

    m_needMerge = mat.m_needMerge;
    m_needSplit = mat.m_needSplit;
    m_cvMat = mat.m_cvMat;
    m_r = mat.m_r;
    m_g = mat.m_g;
    m_b = mat.m_b;
    m_hMat = mat.m_hMat;

    return *this;
}

rv::ReMat& rv::ReMat::operator=(const cv::Mat& mat)
{
    *this = rv::ReMat(mat);

    return *this;
}

rv::ReMat& rv::ReMat::operator=(const HMat& mat)
{
    *this = rv::ReMat(mat);

    return *this;
}

#pragma endregion

#pragma region 数据设置

void rv::ReMat::_setData(const cv::Mat& src, bool copyData)
{
    clear();
    if (src.empty())
    {
        return;
    }

    m_cvMat = copyData ? src.clone() : src;
    if (m_cvMat.channels() > 1)
    {
        m_needSplit = true;
    }

    updateImageInfo();
}

void rv::ReMat::_setData(const HMat& src, bool copyData)
{
    clear();
    if (!src.IsInitialized() || src.CountObj() == 0)
    {
        return;
    }

    if (!copyData)
    {
        m_hMat = src;

        if (m_hMat.CountChannels() == 1)
        {
            //获取其内存地址
            HalconCpp::HString type;
            Hlong width, height;
            void* ptr = m_hMat.GetImagePointer1(&type, &width, &height);

            //指向其内存
            m_cvMat = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, ptr);
        }
        else
        {
            //获取其内存地址
            HalconCpp::HString type;
            Hlong width, height;
            void* rptr = nullptr;
            void* gptr = nullptr;
            void* bptr = nullptr;
            m_hMat.GetImagePointer3(&rptr, &gptr, &bptr, &type, &width, &height);

            //指向其内存
            m_r = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, rptr);
            m_g = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, gptr);
            m_b = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, bptr);

            m_needMerge = true;
        }
    }
    else
    {
        HalconCpp::HTuple channels;
        HalconCpp::CountChannels(src, &channels);
        if (channels.L() == 1)
        {
            //获取其内存地址
            HalconCpp::HString type;
            Hlong width, height;
            void* ptr = src.GetImagePointer1(&type, &width, &height);

            //内存拷贝
            m_cvMat = cv::Mat((int)height, (int)width, CV_8UC1);
            memcpy(m_cvMat.data, ptr, static_cast<size_t>(height) * width);
        }
        else
        {
            //获取其内存地址
            HalconCpp::HString type;
            Hlong width, height;
            void* rptr = nullptr;
            void* gptr = nullptr;
            void* bptr = nullptr;
            src.GetImagePointer3(&rptr, &gptr, &bptr, &type, &width, &height);

            //内存拷贝
            m_r = cv::Mat((int)height, (int)width, CV_8UC1);
            memcpy(m_r.data, rptr, static_cast<size_t>(height) * width);
            m_g = cv::Mat((int)height, (int)width, CV_8UC1);
            memcpy(m_g.data, gptr, static_cast<size_t>(height) * width);
            m_b = cv::Mat((int)height, (int)width, CV_8UC1);
            memcpy(m_b.data, bptr, static_cast<size_t>(height) * width);

            m_needMerge = true;
        }
    }

    updateImageInfo();
}

void rv::ReMat::_setData(int rows, int cols, int channels, void* data, bool copyData)
{
    cv::Mat image = cv::Mat(rows, cols, CV_8UC(channels), data);
    _setData(image, copyData);

}

void rv::ReMat::_setData(int rows, int cols, void* data, BayerType bayerType)
{
    clear();

#if ENABLE_HCORE

    HMat bayerMat;
    bayerMat.GenImage1Extern("byte", cols, rows, (uchar*)data, nullptr);

    switch (bayerType)
    {
    case rv::ReMat::Bayer_GR:
        m_hMat = bayerMat.CfaToRgb("bayer_gr", "bilinear");
        break;
    case rv::ReMat::Bayer_RG:
        m_hMat = bayerMat.CfaToRgb("bayer_rg", "bilinear");
        break;
    case rv::ReMat::Bayer_GB:
        m_hMat = bayerMat.CfaToRgb("bayer_gb", "bilinear");
        break;
    case rv::ReMat::Bayer_BG:
        m_hMat = bayerMat.CfaToRgb("bayer_bg", "bilinear");
        break;
    default:
        break;
    }

    //获取其内存地址
    HalconCpp::HString type;
    Hlong width, height;
    void* rptr = nullptr;
    void* gptr = nullptr;
    void* bptr = nullptr;
    m_hMat.GetImagePointer3(&rptr, &gptr, &bptr, &type, &width, &height);

    //指向其内存
    m_r = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, rptr);
    m_g = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, gptr);
    m_b = cv::Mat(cv::Size((int)height, (int)width), CV_8UC1, bptr);

    m_needMerge = true;

#else

    cv::Mat src = cv::Mat(rows, cols, CV_8UC1, data);
    switch (bayerType)
    {
    case rv::ReMat::Bayer_GR:
        cv::cvtColor(src, m_cvMat, cv::COLOR_BayerGR2BGR);
        break;
    case rv::ReMat::Bayer_RG:
        cv::cvtColor(src, m_cvMat, cv::COLOR_BayerRG2BGR);
        break;
    case rv::ReMat::Bayer_GB:
        cv::cvtColor(src, m_cvMat, cv::COLOR_BayerGB2BGR);
        break;
    case rv::ReMat::Bayer_BG:
        cv::cvtColor(src, m_cvMat, cv::COLOR_BayerBG2BGR);
        break;
    default:
        break;
    }
    m_needSplit = true;

#endif // ENABLE_HCORE

    updateImageInfo();
}

#pragma endregion

#pragma region 功能函数

bool rv::ReMat::read(const std::string& file)
{
    cv::Mat image = cv::imread(file, cv::IMREAD_UNCHANGED);
    if (!image.empty())
    {
        if (image.channels() == 4)
        {
            cv::cvtColor(image, image, cv::COLOR_BGRA2BGR);
        }
        _setData(image);
        return true;
    }

    return false;
}

void rv::ReMat::clear()
{
    m_cvMat = cv::Mat();
    m_r = cv::Mat();
    m_g = cv::Mat();
    m_b = cv::Mat();
    m_hMat = HMat();
    m_needSplit = false;
    m_needMerge = false;

    m_empty = true;
    m_rows = 0;
    m_cols = 0;
    m_step = 0;
    m_channels = 0;
}

rv::ReMat rv::ReMat::clone() const
{
    rv::ReMat remat(*this, true);

    return remat;
}

bool rv::ReMat::empty() const
{
    return m_empty;
}

cv::Mat rv::ReMat::getMat() const
{
    if (!m_empty)
    {
        //如果数据在rgb离散通道而非_src图像中,则构造_src图像
        if (m_needMerge)
        {
            std::vector<cv::Mat> rgbMat(3);
            rgbMat[0] = m_b;
            rgbMat[1] = m_g;
            rgbMat[2] = m_r;

            //将离散通道组成混合通道(opencv格式),为避免每次调用这个方法都计算一次,将计算结果作为缓存保存在_src之中
            cv::merge(rgbMat, const_cast<rv::ReMat*>(this)->m_cvMat);

            const_cast<bool&>(m_needMerge) = false;
        }

        return m_cvMat;
    }

    return cv::Mat();
}

HMat rv::ReMat::getHMat() const
{
    HMat image;

    if (!m_empty)
    {
        if (m_channels == 1)
        {
            image.GenImage1Extern("byte", (Hlong)m_cvMat.cols, (Hlong)m_cvMat.rows, m_cvMat.data, nullptr);
        }
        else
        {
            //如果数据在m_cvMat通道而并非离散的rgb通道,则分离其通道
            if (m_needSplit)
            {
                //分离图像
                std::vector<cv::Mat> imageChannel;
                cv::split(m_cvMat, imageChannel);

                if (imageChannel.size() == 3)
                {
                    const_cast<cv::Mat&>(m_b) = imageChannel[0];
                    const_cast<cv::Mat&>(m_g) = imageChannel[1];
                    const_cast<cv::Mat&>(m_r) = imageChannel[2];
                    const_cast<bool&>(m_needSplit) = false;
                }
            }

            image.GenImage3Extern(HalconCpp::HString("byte"), (Hlong)m_cvMat.cols, (Hlong)m_cvMat.rows,
                static_cast<void*>(m_r.data),
                static_cast<void*>(m_g.data),
                static_cast<void*>(m_b.data), nullptr);
        }
    }

    return image;
}

cv::Mat rv::ReMat::getRChannel() const
{
    if (!m_empty && (m_channels == 3))
    {
        if (m_needSplit)
        {
            //分离图像
            std::vector<cv::Mat> imageChannel;
            cv::split(m_cvMat, imageChannel);

            if (imageChannel.size() == 3)
            {
                const_cast<cv::Mat&>(m_b) = imageChannel[0];
                const_cast<cv::Mat&>(m_g) = imageChannel[1];
                const_cast<cv::Mat&>(m_r) = imageChannel[2];
                const_cast<bool&>(m_needSplit) = false;
            }
        }

        return m_r;
    }

    return cv::Mat();
}

cv::Mat rv::ReMat::getGChannel() const
{
    if (!m_empty && (m_channels == 3))
    {
        if (m_needSplit)
        {
            //分离图像
            std::vector<cv::Mat> imageChannel;
            cv::split(m_cvMat, imageChannel);

            if (imageChannel.size() == 3)
            {
                const_cast<cv::Mat&>(m_b) = imageChannel[0];
                const_cast<cv::Mat&>(m_g) = imageChannel[1];
                const_cast<cv::Mat&>(m_r) = imageChannel[2];
                const_cast<bool&>(m_needSplit) = false;
            }
        }

        return m_g;
    }

    return cv::Mat();
}

cv::Mat rv::ReMat::getBChannel() const
{
    if (!m_empty && (m_channels == 3))
    {
        if (m_needSplit)
        {
            //分离图像
            std::vector<cv::Mat> imageChannel;
            cv::split(m_cvMat, imageChannel);

            if (imageChannel.size() == 3)
            {
                const_cast<cv::Mat&>(m_b) = imageChannel[0];
                const_cast<cv::Mat&>(m_g) = imageChannel[1];
                const_cast<cv::Mat&>(m_r) = imageChannel[2];
                const_cast<bool&>(m_needSplit) = false;
            }
        }

        return m_b;
    }

    return cv::Mat();
}

HMat rv::ReMat::deepCopy(const HMat& src)
{
    HMat image;

#ifdef ENABLE_HCORE

    if (src.IsInitialized() && src.CountObj() > 0)
    {
        int channels = (int)src.CountChannels();

        HalconCpp::HString type;
        Hlong width, height;

        if (channels == 1)
        {
            //获取指针
            void* ptr = src.GetImagePointer1(&type, &width, &height);
            //构造新实例
            image.GenImage1(type, width, height, ptr);
        }
        else
        {
            void* rptr = nullptr;
            void* gptr = nullptr;
            void* bptr = nullptr;
            src.GetImagePointer3(&rptr, &gptr, &bptr, &type, &width, &height);

            //构造新实例
            image.GenImage3(type, width, height, rptr, gptr, bptr);
        }
    }

#else

    image = src.clone();

#endif

    return image;
}

void rv::ReMat::updateImageInfo()
{
    if (m_cvMat.empty() && m_r.empty())
    {
        m_empty = true;
        m_rows = 0;
        m_cols = 0;
        m_step = 0;
        m_channels = 0;
        return;
    }

    if (m_needMerge)
    {
        m_rows = m_r.rows;
        m_cols = m_r.cols;
        m_step = (int)m_r.step * 3;
        m_channels = 3;
    }
    else
    {
        m_rows = m_cvMat.rows;
        m_cols = m_cvMat.cols;
        m_step = (int)m_cvMat.step;
        m_channels = m_cvMat.channels();
    }
    m_empty = false;

}

#pragma endregion
