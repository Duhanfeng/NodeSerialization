#include "flowUnit.h"
#include <VisionFlow/timer.h>

#pragma region 流程控制

void qv::FlowUnit::clear()
{
    nodes.clear();
    connection.reset();

}

void qv::FlowUnit::appendNode(std::unique_ptr<NodeBase>& node)
{
    if (node != nullptr)
    {
        node->parent = this;
        connection.addNode(node.get());

        //注册功能函数
        node->getSuperiorNodeVariant = std::bind(&NodeConnection::getSuperiorNodeVariant, &(this->connection), std::placeholders::_1, std::placeholders::_2);
        node->getCurrentNodeVariant = std::bind(&NodeConnection::getCurrentNodeVariant, &(this->connection), std::placeholders::_1, std::placeholders::_2);

        //添加入列表之中(move之后,旧对象不可再使用,其对象已经不可靠)
        nodes.push_back(std::move(node));
    }

}

void qv::FlowUnit::removeNode(int index)
{
    if ((index >= 0) && (index < (int)nodes.size()))
    {
        nodes[index]->getSuperiorNodeVariant = nullptr;
        nodes[index]->getCurrentNodeVariant = nullptr;
        connection.remove(index);
        nodes.erase(nodes.cbegin() + index);
    }
}

void qv::FlowUnit::moveUpNode(int index)
{
    //index为0时没有上移的必要
    if ((index > 0) && (index < (int)nodes.size()))
    {
        connection.moveUpNode(index);

        std::unique_ptr<NodeBase> nodePtr = std::move(nodes[index]);
        nodes.erase(nodes.cbegin() + index);
        nodes.insert(nodes.cbegin() + index - 1, std::move(nodePtr));
    }
}

void qv::FlowUnit::moveDownNode(int index)
{
    //index为最后一位时没有下移的必要
    if ((index >= 0) && (index < (int)nodes.size() - 1))
    {
        connection.moveDownNode(index);

        std::unique_ptr<NodeBase> nodePtr = std::move(nodes[index]);
        nodes.erase(nodes.cbegin() + index);
        nodes.insert(nodes.cbegin() + index + 1, std::move(nodePtr));
    }

}

void qv::FlowUnit::recoverNodes()
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] == nullptr)
        {
            continue;
        }

        nodes[i]->parent = this;

        //注册功能函数
        nodes[i]->getSuperiorNodeVariant = std::bind(&NodeConnection::getSuperiorNodeVariant, &(this->connection), std::placeholders::_1, std::placeholders::_2);
        nodes[i]->getCurrentNodeVariant = std::bind(&NodeConnection::getCurrentNodeVariant, &(this->connection), std::placeholders::_1, std::placeholders::_2);
    }

    //将参考图片设置进默认的输入节点中
    if (!referImage.empty())
    {
        setImage(referImage);
    }

}

void qv::FlowUnit::setImage(rv::InputReMat image)
{
    Variant* var = connection.getCurrentNodeVariant("-1", "InputImage");
    if (var != nullptr)
    {
        var->setValue(image);
    }

}

void qv::FlowUnit::setReferImage(rv::InputReMat image)
{
    setImage(image);
    referImage = image;
}

rv::ReMat qv::FlowUnit::getImage()
{
    Variant* var = connection.getCurrentNodeVariant("-1", "InputImage");
    if (var == nullptr)
    {
        return rv::ReMat();
    }

    return var->getReMat();
}

#if 0

qv::RunStatus qv::FlowUnit::run()
{
    RunStatus runStatus;
    qv::Timer timer;
    drawingInfos.clear();

    rv::ReMat image = getImage();
    if (image.empty())
    {
        return RunStatus(0, RunResult::Error, "输入图像无效");
    }

    runStatus.drawingInfo.setName("Result");
    runStatus.drawingInfo.setBackgroundImage(image);

    ResultDrawingInfo info;
    info.setName("InputImage");
    info.setBackgroundImage(image);
    drawingInfos.push_back(info);

    m_runResultMap.clear();

    //开始解析连接信息
    for (size_t i = 0; i < nodes.size(); i++)
    {
        //如果满足前置条件,则运行
        if (checkPrecondition(nodes[i]->guid) && nodes[i]->isEnable)
        {
            //执行节点
            RunStatus nodeStatus = nodes[i]->run();
            m_runResultMap[nodes[i]->guid] = nodeStatus.isOk;

            //记录输出信息
            drawingInfos.push_back(nodeStatus.drawingInfo);

            //统一将所有的节点结果整合到一个中
            //if (nodes[i]->nodeID > (int)PreprocessNodeEnum::EndValue)
            {
                const std::vector<qv::Variant>& vars = nodeStatus.drawingInfo.getVariants();

                for (const qv::Variant& var : vars)
                {
                    if (var.type() != Variant::VariantType::Image)
                    {
                        runStatus.drawingInfo.getVariants().push_back(var);
                    }
                }
            }

            //如果执行异常,则直接退出
            if (nodeStatus.result != RunResult::Accept)
            {
                runStatus.result = nodeStatus.result;
                runStatus.message = nodes[i]->name + ": " + nodeStatus.message;
                break;
            }
        }
        else
        {
            nodes[i]->triggerNonRun();
            m_runResultMap[nodes[i]->guid] = false;
        }
    }
    drawingInfos.push_back(runStatus.drawingInfo);

    runStatus.totalTime = timer.elapsed() * 1000;

    return runStatus;
}
#else

qv::RunStatus qv::FlowUnit::run(rv::IReWindow* rewindow)
{
    RunStatus runStatus;
    qv::Timer timer;

    rv::ReMat image = getImage();
    if (image.empty())
    {
        return RunStatus(0, RunResult::Error, "输入图像无效");
    }

    if (rewindow != nullptr)
    {
        rewindow->dispImage(image);
    }

    m_runResultMap.clear();

    //开始解析连接信息
    for (size_t i = 0; i < nodes.size(); i++)
    {
        //如果满足前置条件,则运行
        if (checkPrecondition(nodes[i]->guid) && nodes[i]->isEnable)
        {
            //执行节点(对于预处理节点,则不显示其内容,避免刷掉之前的图形)
            RunStatus nodeStatus = nodes[i]->run(checkIsPreProcessNode(nodes[i]->nodeID) ? nullptr : rewindow);
            m_runResultMap[nodes[i]->guid] = nodeStatus.isOk;

            //如果执行异常,则直接退出
            if (nodeStatus.result != RunResult::Accept)
            {
                runStatus.result = nodeStatus.result;
                runStatus.message = nodes[i]->name + ": " + nodeStatus.message;
                break;
            }
        }
        else
        {
            nodes[i]->triggerNonRun();
            m_runResultMap[nodes[i]->guid] = false;
        }
    }

    if (rewindow != nullptr)
    {
        rewindow->flushBuffer();
    }

    runStatus.totalTime = timer.elapsed() * 1000;

    return runStatus;
}

qv::RunStatus qv::FlowUnit::run(rv::IReWindows* rewindows)
{
    RunStatus runStatus;
    qv::Timer timer;
    
    if (rewindows != nullptr)
    {
        rewindows->reset();
    }

    rv::ReMat image = getImage();
    if (image.empty())
    {
        return RunStatus(0, RunResult::Error, "输入图像无效");
    }

    rv::IReWindow* resultWindow = nullptr;

    if (rewindows != nullptr)
    {
        rewindows->setImage(image);

        //创建结果整合列
        resultWindow = rewindows->getNewWindow();
        resultWindow->setName("Result");

        //创建输入列
        rv::IReWindow* window = rewindows->getNewWindow();
        window->setName("InputImage");
    }

    m_runResultMap.clear();

    //开始解析连接信息
    for (size_t i = 0; i < nodes.size(); i++)
    {
        //如果满足前置条件,则运行
        if (checkPrecondition(nodes[i]->guid) && nodes[i]->isEnable)
        {
            rv::IReWindow* window = nullptr;
            if (rewindows != nullptr)
            {
                window = rewindows->getNewWindow();
                window->setName(nodes[i]->name);
            }

            //执行节点
            RunStatus nodeStatus = nodes[i]->run(window);
            m_runResultMap[nodes[i]->guid] = nodeStatus.isOk;

            //形状拼接
            if (resultWindow != nullptr)
            {
                resultWindow->append(window);
            }

            //如果执行异常,则直接退出
            if (nodeStatus.result != RunResult::Accept)
            {
                runStatus.result = nodeStatus.result;
                runStatus.message = nodes[i]->name + ": " + nodeStatus.message;
                break;
            }
        }
        else
        {
            nodes[i]->triggerNonRun();
            m_runResultMap[nodes[i]->guid] = false;
        }
    }

    if (rewindows != nullptr)
    {
        rewindows->flushBuffer();
    }

    runStatus.totalTime = timer.elapsed() * 1000;

    return runStatus;
}

#endif // 0

bool qv::FlowUnit::checkPrecondition(const std::string& guid)
{
    //如果连接器里并没有相关信息,或者是明确说明不使用前置条件,则直接判断为true;否则进行结果判断
    if ((connection.nodePrecondition.find(guid) != connection.nodePrecondition.end()) && connection.nodePrecondition[guid].useThis)
    {
        if (m_runResultMap.find(connection.nodePrecondition[guid].dstGuid) != m_runResultMap.end())
        {
            return m_runResultMap[connection.nodePrecondition[guid].dstGuid] == connection.nodePrecondition[guid].isOkRun;
        }
    }

    return true;
}

bool qv::FlowUnit::checkIsPreProcessNode(int id)
{
    return (id >= 100000) && (id <= 199999);
}

#pragma endregion

#pragma region 结果打包器

std::string qv::FlowUnit::getValueString(const qv::OutputSelection& selection)
{

    return outputPacket.getValueString(connection, selection);
}

std::string qv::FlowUnit::getOutputString()
{

    return outputPacket.getOutputString(connection);
}

#pragma endregion

#pragma region 连接器接口

void qv::FlowUnit::getInputSources(qv::NodeBase* node, Variant::VariantType type, std::vector<qv::NodeOutputInfo>& inputInfos)
{
    inputInfos.clear();

    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return;
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return;
    }

    //获取当前输入项的类型
    flowUnit->connection.getCurrentSourceInfo(node->guid, type, inputInfos);

}

void qv::FlowUnit::getSuperiorNodeInfo(qv::NodeBase* node, const std::string& inputName, qv::NodeOutputInfo& info)
{
    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return;
    }
    bool isFindParam = false;
    for (size_t i = 0; i < node->inputs.size(); i++)
    {
        if (node->inputs[i].paramName == inputName)
        {
            isFindParam = true;
            break;
        }
    }
    if (!isFindParam)
    {
        //输入名不存在
        return;
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return;
    }

    //获取当前的输入源
    flowUnit->connection.getSuperiorNodeInfo(node->guid, inputName, info);

}

void qv::FlowUnit::reconnectInputSource(qv::NodeBase* node, const std::string& inputName, const NodeOutputInfo& info)
{
    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return;
    }
    bool isFindParam = false;
    for (size_t i = 0; i < node->inputs.size(); i++)
    {
        if (node->inputs[i].paramName == inputName)
        {
            isFindParam = true;
            break;
        }
    }
    if (!isFindParam)
    {
        //输入名不存在
        return;
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return;
    }

    //重建连接节点
    flowUnit->connection.connect(node->guid, inputName, info);

}

void qv::FlowUnit::reconnectInputSource(qv::NodeBase* node, const std::string& inputName, const std::vector<qv::NodeOutputInfo>& inputInfos, int index)
{
    if ((index >= 0) && (index < (int)inputInfos.size()))
    {
        reconnectInputSource(node, inputName, inputInfos[index]);
    }

}

void qv::FlowUnit::getForwardNodeInfos(qv::NodeBase* node, std::vector<NodeInfo>& infos)
{
    infos.clear();

    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return;
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return;
    }

    for (size_t i = 0; i < flowUnit->nodes.size(); i++)
    {
        if (flowUnit->nodes[i]->guid == node->guid)
        {
            return;
        }
        else
        {
            infos.push_back(flowUnit->nodes[i]->getInfo());
        }
    }

    //如果运行到这里,表明flowUnit->nodes里面并没有node,直接清空names
    infos.clear();

}

qv::NodePrecondition qv::FlowUnit::getNodePrecondition(qv::NodeBase* node)
{
    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return NodePrecondition();
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return NodePrecondition();
    }

    //提取其相关信息
    auto itr = flowUnit->connection.nodePrecondition.find(node->guid);
    if (itr != flowUnit->connection.nodePrecondition.end())
    {
        return itr->second;
    }
    
    return NodePrecondition();
}

void qv::FlowUnit::setNodePrecondition(qv::NodeBase* node, const qv::NodePrecondition& precondition)
{
    //数据校验
    if ((node == nullptr) || (node->parent == nullptr))
    {
        return;
    }

    //获取其流程单元
    FlowUnit* flowUnit = static_cast<FlowUnit*>(node->parent);
    if (flowUnit == nullptr)
    {
        //流程单元不存在
        return;
    }

    //提取其相关信息
    auto itr = flowUnit->connection.nodePrecondition.find(node->guid);
    if (itr != flowUnit->connection.nodePrecondition.end())
    {
        itr->second = precondition;
    }

}

#pragma endregion
