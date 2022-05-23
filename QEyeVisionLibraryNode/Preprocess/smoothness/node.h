#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>

namespace qv
{
    enum class SmoothnessMethod
    {
        MeanFilter = 0,     //均值滤波
        MedianFilter,       //中值滤波
        GaussianFilter,     //高斯滤波
        //BilateralFilter,    //双边滤波,比较耗时,移除
    };

    class SmoothnessNode : public NodeBase
    {
    public:
        SmoothnessNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;

    public:
        SmoothnessMethod method = SmoothnessMethod::MeanFilter;
        int kernelSize = 3;             //滤波核,不得为偶数

    public:
        NodeParamDescription outputImage = { "Output", u8"图像", Variant::VariantType::Image };

    private:
        cv::Ptr<rv::IPreprocess> IPreprocess = nullptr;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
            ar& BOOST_SERIALIZATION_NVP(method);
            ar& BOOST_SERIALIZATION_NVP(kernelSize);
        }

    };

}

//BOOST_CLASS_EXPORT(qv::SmoothnessNode)
//BOOST_CLASS_EXPORT_KEY(qv::SmoothnessNode)
