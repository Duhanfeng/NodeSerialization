#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

#include <ReVisionLib/revision.hpp>
#include "variant/variant.h"

namespace qv
{
    enum class RunResult
    {
        Error = -1,     //错误
        Accept = 0,     //接受
        Warning,        //警告
        Reject,         //拒绝
    };

    class RunStatus
    {
    public:
        bool isOk = false;      //代表本次执行成功
        double totalTime = 0;
        RunResult result;       //result和isOk的区别: result代表的是工程级别的异常,而isOk代表视觉处理的结果是否符合预期;
        std::string message;
        RunStatus() : result(RunResult::Accept), message(""){}
        RunStatus(double _time) : totalTime(_time), result(RunResult::Accept), message("") {}
        RunStatus(double _time, RunResult _result, std::string _message) : totalTime(_time),  result(_result), message(_message) {}
    };

    using connect_callback_t = std::function<Variant* (const std::string&, const std::string&)>;

    enum class DefaultSource
    {
        First,  //第一个
        Last,   //最后一个
        Null,   //不连接
    };

    class NodeParamDescription
    {
    public:
        std::string paramName;      //参数名
        std::string description;    //参数描述
        Variant::VariantType type = Variant::VariantType::Image;
        DefaultSource defaultSource = DefaultSource::Last;

        NodeParamDescription() {};
        NodeParamDescription(const std::string& _paramName, const std::string& _description, Variant::VariantType _type) :
            paramName(_paramName), description(_description), type(_type) {};
        NodeParamDescription(const std::string& _paramName, const std::string& _description, Variant::VariantType _type, DefaultSource _defaultSource) :
            paramName(_paramName), description(_description), type(_type), defaultSource(_defaultSource) {};
    };

    class NodeInfo
    {
    public:
        std::string guid;
        std::string name;
        std::string description;
        int nodeID = -1;

    };

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
        virtual std::string className() { return "Node"; }
        virtual std::string displayName() { return u8"节点单元"; }

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
            ar& BOOST_SERIALIZATION_NVP(inputs);
            ar& BOOST_SERIALIZATION_NVP(outputs);
        }
    };
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(qv::NodeBase)
