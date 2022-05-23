#pragma once

#include <QEyeVisionLibrary/QEyeVisionLib.hpp>
#include "serialization.h"
#include <iostream>

#pragma execution_character_set("utf-8") 

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
        SmoothnessNode(void* _parent = nullptr) : NodeBase(_parent)
        {
            name = "SmoothnessNode";
            description = u8"平滑";
            nodeID = 100002;
            isEnableRefer = false;

            inputs.push_back(inputImage);
            outputs.push_back(outputImage);

            IPreprocess = rv::IPreprocess::create();

        }
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override
        {
            std::cout << "run: SmoothnessNode" << std::endl;

            return RunStatus();
        }

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
BOOST_CLASS_EXPORT(qv::SmoothnessNode)

inline void tesetNode1()
{
    qv::NodeBase* node = new qv::SmoothnessNode();
    node->nodeID = 9999;
    std::cout << node->nodeID << std::endl;
    std::cout << node->description << std::endl;
    serializeXml(node, "_node.pp");
    qv::NodeBase* node2;
    deserializeXml(node2, "_node.pp");
    std::cout << node2->nodeID << std::endl;
    std::cout << node2->description << std::endl;
    node2->runImage(rv::ReMat(), nullptr);
    

}
