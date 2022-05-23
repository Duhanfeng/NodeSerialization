#pragma once

#include "nodeBase.h"
#include "variant.h"

namespace qv
{
    class NodeOutputInfo
    {
    public:
        std::string nodeGuid;       //当前节点的guid
        std::string nodeName;       //当前节点名

        std::string paramName;      //输出参数名
        Variant::VariantType type = Variant::VariantType::Empty;  //默认类型-空
    };

    class NodePrecondition
    {
    public:
        bool useThis = false;       //是否进行上级guid结果判断
        std::string dstGuid;        //先决的guid,根据此guid的执行结果进行是否需要执行的判断
        bool isOkRun = true;        //true:先决的guid在ok的前提下运行;flase:先决的guid在ng的前提下运行
    };

    class NodeConnection
    {
    public:
        class NodeOutput
        {
        public:
            NodeOutputInfo info;    //相关信息
            Variant variant;        //输出变量
        };

    public:

        NodeConnection();

        //节点的增删改查
        void reset();
        void addNode(const NodeBase* node); //注册一个节点
        void connect(const std::string& guid, const std::string& paramName, NodeOutputInfo info); 
        void remove(int index);
        void moveUpNode(int index);
        void moveDownNode(int index);

        //输入源配置相关
        void getCurrentSourceInfo(const std::string& guid, Variant::VariantType type, std::vector<NodeOutputInfo>& inputInfo); //获取当前节点所支持的上级节点
        void setCurrentSourceToDefault(const std::string& guid, const std::string& paramName, Variant::VariantType type, DefaultSource def);  //设置当前输入源到默认上级节点
        void getSuperiorNodeInfo(const std::string& guid, const std::string& paramName, NodeOutputInfo& info);

        //数据调用接口
        Variant* getSuperiorNodeVariant(const std::string& guid, const std::string& paramName);     //获取上级节点传到本节点的数据
        Variant* getCurrentNodeVariant(const std::string& guid, const std::string& paramName);      //获取当前节点传出的数据

        //检查连接的合理性(一般在节点之间的顺序改变后调用)
        void checkConnectRationality(); 

    public:
        std::vector<std::string> nodeIndexs;    //节点索引,记录每个节点的顺序,下级节点可以连接到上级节点,但是上级不能连接到下级或者本身
        std::map<std::string, std::map<std::string, NodeOutput>> nodeCurrent;       //输出节点集合,第一个key是nodeGuid,第二个key为outputName
        std::map<std::string, std::map<std::string, NodeOutputInfo>> nodeSuperior;  //记录当前输入节点的上级输入源信息,第一个key是nodeGuid,第二个key为inputName
        std::map<std::string, NodePrecondition> nodePrecondition;                   //记录当前节点的执行前置条件,""为依据控件本身的isEnable属性,其他为需要判断对应guid的结果

        //获取guid在nodeIndexs里面的顺序
        int getGuidIndex(const std::string& guid);
    };

}