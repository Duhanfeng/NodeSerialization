#include "nodeConnection.h"

using namespace qv;

NodeConnection::NodeConnection()
{
    reset();
}

void NodeConnection::reset()
{
    //添加一个前置输出源: -1,image 用于表示节点传入的图像
    NodeOutput output;
    output.info.nodeGuid = "-1";
    output.info.nodeName = "";
    output.info.paramName = "InputImage";
    output.info.type = qv::Variant::VariantType::Image;
    output.variant.setValue(rv::ReMat());

    nodeCurrent.clear();
    nodeCurrent[output.info.nodeGuid][output.info.paramName] = output;
    nodeIndexs.clear();
    nodeIndexs.push_back("-1");
    nodeSuperior.clear();
}

void NodeConnection::addNode(const NodeBase* node)
{
    if (node == nullptr)
    {
        return;
    }

    //判断是否已经注册过此节点,如果有则退出,否则注册进节点索引列表中
    if (std::find(nodeIndexs.begin(), nodeIndexs.end(), node->guid) != nodeIndexs.end())
    {
        return;
    }
    nodeIndexs.push_back(node->guid);

    //注册输出节点
    for (size_t i = 0; i < node->outputs.size(); i++)
    {
        NodeOutput output;
        output.info.nodeGuid = node->guid;
        output.info.nodeName = node->name;
        output.info.paramName = node->outputs[i].paramName;
        output.info.type = node->outputs[i].type;
        output.variant.setType(node->outputs[i].type);

        //存储输出数据对象
        nodeCurrent[output.info.nodeGuid][output.info.paramName] = output;
    }

    //获取所有支持的输入节点,并默认链接到最后一个
    for (size_t i = 0; i < node->inputs.size(); i++)
    {
        setCurrentSourceToDefault(node->guid, node->inputs[i].paramName, node->inputs[i].type, node->inputs[i].defaultSource);
    }

    //更新其运行的前置条件
    nodePrecondition[node->guid] = NodePrecondition();

}

void NodeConnection::connect(const std::string& guid, const std::string& paramName, NodeOutputInfo info)
{
    nodeSuperior[guid][paramName] = info;

}

void NodeConnection::remove(int index)
{
    index += 1; //输入源节点占了一个位置

    if ((index >= 1) && (index < (int)nodeIndexs.size()))
    {
        //从nodeIndexs中删除
        std::string guid = nodeIndexs[index];
        nodeIndexs.erase(nodeIndexs.cbegin() + index);

        //从nodeCurrent里面移除掉相关的资源
        auto outputItor = nodeCurrent.find(guid);
        if (outputItor != nodeCurrent.end())
        {
            nodeCurrent.erase(outputItor);
        }

        //从nodePrecondition中删除相关资源
        auto preconditionItor = nodePrecondition.find(guid);
        if (preconditionItor != nodePrecondition.end())
        {
            nodePrecondition.erase(preconditionItor);
        }

        checkConnectRationality();
    }
}

void NodeConnection::moveUpNode(int index)
{
    index += 1; //输入源节点占了一个位置

    //index为1时没有上移的必要(0必须为默认输入源)
    if ((index > 1) && (index < (int)nodeIndexs.size()))
    {
        std::string  guid = nodeIndexs[index];
        nodeIndexs.erase(nodeIndexs.cbegin() + index);
        nodeIndexs.insert(nodeIndexs.cbegin() + index - 1, guid);

        checkConnectRationality();
    }

}

void NodeConnection::moveDownNode(int index)
{
    index += 1; //输入源节点占了一个位置

    //index为最后一位时没有下移的必要
    if ((index >= 1) && (index < (int)nodeIndexs.size()))
    {
        std::string  guid = nodeIndexs[index];
        nodeIndexs.erase(nodeIndexs.cbegin() + index);
        nodeIndexs.insert(nodeIndexs.cbegin() + index + 1, guid);

        checkConnectRationality();
    }

}

void NodeConnection::getCurrentSourceInfo(const std::string& guid, Variant::VariantType type, std::vector<NodeOutputInfo>& inputInfo)
{
    inputInfo.clear();

    //获取当前节点在列表中的序号,如果当前节点尚未注册,则直接退出
    auto currentItor = std::find(nodeIndexs.cbegin(), nodeIndexs.cend(), guid);
    if (currentItor == nodeIndexs.cend())
    {
        return;
    }

    //遍历当前节点之前的节点,获取其符合参数类型的节点信息
    for (auto itor = nodeIndexs.cbegin(); itor != currentItor; itor++)
    {
        std::string guid = *itor;
        if (nodeCurrent.find(guid) != nodeCurrent.end())
        {
            for (auto itor2 = nodeCurrent[guid].begin(); itor2 != nodeCurrent[guid].end(); itor2++)
            {
                if (itor2->second.info.type == type)
                {
                    inputInfo.push_back(itor2->second.info);
                }
            }
        }
    }

}

void NodeConnection::setCurrentSourceToDefault(const std::string& guid, const std::string& paramName, Variant::VariantType type, DefaultSource def)
{
    std::vector<NodeOutputInfo> infos;
    getCurrentSourceInfo(guid, type, infos);
    if (infos.size() > 0)
    {
        switch (def)
        {
        case qv::DefaultSource::First:
            connect(guid, paramName, infos[0]);
            break;
        case qv::DefaultSource::Last:
            connect(guid, paramName, infos[infos.size() - 1]);
            break;
        case qv::DefaultSource::Null:
            connect(guid, paramName, NodeOutputInfo());
            break;
        }
    }
    else
    {
        connect(guid, paramName, NodeOutputInfo());
    }
}

void qv::NodeConnection::getSuperiorNodeInfo(const std::string& guid, const std::string& paramName, NodeOutputInfo& info)
{
    if ((nodeSuperior.find(guid) != nodeSuperior.end()) && (nodeSuperior[guid].find(paramName) != nodeSuperior[guid].end()))
    {
        info = nodeSuperior[guid][paramName];
    }
    else
    {
        info = NodeOutputInfo();
    }
}

//获取上级节点传到本节点的数据
Variant* NodeConnection::getSuperiorNodeVariant(const std::string& guid, const std::string& paramName)
{
    if ((nodeSuperior.find(guid) != nodeSuperior.end()) && (nodeSuperior[guid].find(paramName) != nodeSuperior[guid].end()))
    {
        NodeOutputInfo& info = nodeSuperior[guid][paramName];

        return getCurrentNodeVariant(info.nodeGuid, info.paramName);
    }

    return nullptr;
}

//获取当前节点传出的数据
Variant* qv::NodeConnection::getCurrentNodeVariant(const std::string& guid, const std::string& paramName)
{
    if ((nodeCurrent.find(guid) != nodeCurrent.end()) && (nodeCurrent[guid].find(paramName) != nodeCurrent[guid].end()))
    {
        return &nodeCurrent[guid][paramName].variant;
    }

    return nullptr;
}

//检查连接的合理性(一般在节点之间的顺序改变后调用)
void NodeConnection::checkConnectRationality()
{
    //遍历nodeSuperior中的所有NodeOutputInfo,检查
    for (auto itor = nodeSuperior.begin(); itor != nodeSuperior.end(); itor++)
    {
        std::string currentGuid = itor->first;
        int currentIndex = getGuidIndex(currentGuid);

        for (auto itor2 = itor->second.begin(); itor2 != itor->second.end(); itor2++)
        {
            //如果有节点指向要删除的节点,则获取其容许的连接内容,切换为最后一个有效内容
            std::string currentParam = itor2->first;
            Variant::VariantType paramType = itor2->second.type;
            std::string superiorGuid = itor2->second.nodeGuid;
            std::string superiorParam = itor2->second.paramName;

            int superiorIndex = getGuidIndex(superiorGuid);

            //如果上级节点已经不存在或者上级节点顺序大于等于当前节点,则重置上级节点
            if ((superiorIndex == -1) || (superiorIndex >= currentIndex))
            {
                setCurrentSourceToDefault(currentGuid, currentParam, paramType, DefaultSource::Last);
            }
        }
    }

    //遍历所有的nodePrecondition,检查
    for (auto itor = nodePrecondition.begin(); itor != nodePrecondition.end(); itor++)
    {
        int index1 = getGuidIndex(itor->first);
        if (itor->second.useThis)
        {
            int index2 = getGuidIndex(itor->second.dstGuid);
            if (index2  == -1)
            {
                itor->second = NodePrecondition();
            }
            else if (index1 <= index2)
            {
                //如果前置的guid比当前的guid还大,则表明异常,复位
                itor->second = NodePrecondition();
            }
        }
    }

}

//获取guid在nodeIndexs里面的顺序
int NodeConnection::getGuidIndex(const std::string& guid)
{
    auto itor = std::find(nodeIndexs.begin(), nodeIndexs.end(), guid);
    if (itor != nodeIndexs.end())
    {
        return (int)std::distance(nodeIndexs.begin(), itor);
    }

    return -1;
}
