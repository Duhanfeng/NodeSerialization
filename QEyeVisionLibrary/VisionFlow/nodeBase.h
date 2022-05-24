#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include <ReVisionLib/ReVision.hpp>
#include "variant/variant.h"
#include "nodeDef.h"

namespace qv
{
    class NodeBase
    {
    public:
        NodeBase(void* _parent);
        virtual ~NodeBase();

        //节点描述
        bool isEnable = true;
        std::string guid;
        std::string name;
        std::string description = "";
        int nodeID = -1;
        void* parent = nullptr;
        NodeInfo getInfo();

        //节点特征(由派生类本身决定)
        //virtual std::string description() const { return "Node"; }
        virtual std::string className() const { return "Node"; }
        virtual std::string displayName() const { return u8"节点单元"; }

        //输入图像
        NodeParamDescription inputImage = { "InputImage", u8"图像", Variant::VariantType::Image };

        //参考坐标及工作区域
        rv::Pose<double> srcPose;       //设置region时参考坐标的位姿,进行仿射变换时需要
        rv::Region region;              //搜索区域,可以根据实际pose进行变换
        bool isEnableRefer = false;     //使能参考点
        bool onlyReferFirst = false;    //仅参考第一个参考点(如果有多个参考点的情况下)
        void setRegion(const rv::Region& region, const rv::Pose<double>& pose = rv::Pose<double>());
        NodeParamDescription referPose = { "ReferPose", u8"参考点", Variant::VariantType::Pose, DefaultSource::Null };    //参考点输入输出参数
        virtual void updateReferPose();
        virtual rv::Region affineTransRegion(const rv::Pose<double>& dstPose);
        virtual rv::Region affineTransRegion(const rv::Region& region, const rv::Pose<double>& dstPose);

        //输入输出描述
        std::vector<NodeParamDescription> inputs;
        std::vector<NodeParamDescription> outputs;
        connect_callback_t getSuperiorNodeVariant = nullptr;
        connect_callback_t getCurrentNodeVariant = nullptr;
        Variant* getInputSource(const NodeParamDescription& input);
        Variant* getOutputSource(const NodeParamDescription& output);

        //输入输出本地空间----在parent无效时使用
        std::map<std::string, Variant> locationInputs;
        std::map<std::string, Variant> locationOutputs;

        //输入输出配置接口(预留,方便通过json等接口进行属性配置)
        virtual void setProperty(const std::string& property, const std::string& value) {}
        virtual std::string getProperty(const std::string& property) { return ""; }
        virtual std::string getPropertyDescriptions() { return ""; }

        //输出结果描述(每次调用run的时候都会更新它)
        RunStatus runResult;

        //重载接口
        virtual RunStatus run(rv::IReWindow* rewindow = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) = 0;
        virtual RunStatus triggerNonRun(rv::IReWindow* rewindow = nullptr);
        virtual void dispose();
        virtual bool write(const std::string& file) { return false; }
        virtual bool read(const std::string& file, bool isKeepGuid = true) { return false; }

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(isEnable);
            ar& BOOST_SERIALIZATION_NVP(guid);
            ar& BOOST_SERIALIZATION_NVP(name);
            ar& BOOST_SERIALIZATION_NVP(description);
            ar& BOOST_SERIALIZATION_NVP(nodeID);
            ar& BOOST_SERIALIZATION_NVP(srcPose);
            ar& BOOST_SERIALIZATION_NVP(region);
            ar& BOOST_SERIALIZATION_NVP(isEnableRefer);
            ar& BOOST_SERIALIZATION_NVP(onlyReferFirst);
            //ar& BOOST_SERIALIZATION_NVP(inputs);
            //ar& BOOST_SERIALIZATION_NVP(outputs);
        }
    };
}

//BOOST_IS_ABSTRACT(qv::NodeBase)
