#pragma once

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
        RunStatus() : result(RunResult::Accept), message("") {}
        RunStatus(double _time) : totalTime(_time), result(RunResult::Accept), message("") {}
        RunStatus(double _time, RunResult _result, std::string _message) : totalTime(_time), result(_result), message(_message) {}
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

    class PropertyDescription
    {
    public:
        std::string name;
        std::string type;
        std::string comments;
    };

}