#pragma once

#include <ReVisionLib/revision.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

#include "variant/variant.h"
#include "nodeBase.h"
#include "nodeConnection.h"
#include "resultOutput.h"

namespace qv
{
    class FlowUnit
    {
    public:
        bool isEnable = true;
        std::string guid;
        std::string name = "";
        std::string description = "";

        //节点交互接口
        void clear();
        void appendNode(std::unique_ptr<NodeBase>& node);
        void removeNode(int index);
        void moveUpNode(int index);
        void moveDownNode(int index);
        void recoverNodes();

        void setImage(rv::InputReMat image);
        rv::ReMat referImage;
        void setReferImage(rv::InputReMat image);   //与setImage不同的是,这个会记录输入的图像(referImage),以便序列化/反序列化后第一时间显示
        rv::ReMat getImage();
        virtual RunStatus run(rv::IReWindow* rewindow = nullptr);
        virtual RunStatus run(rv::IReWindows* rewindows);

    public:
        std::string getValueString(const OutputSelection& selection);
        std::string getOutputString();

    public:
        //连接器接口(由于子节点并不能直接控制NodeConnection,所以由以下公共接口供node进行连接信息管理)
        static void getInputSources(qv::NodeBase* node, Variant::VariantType type, std::vector<qv::NodeOutputInfo>& inputInfos);
        static void getSuperiorNodeInfo(qv::NodeBase* node, const std::string& inputName, NodeOutputInfo& info);
        static void reconnectInputSource(qv::NodeBase* node, const std::string& inputName, const NodeOutputInfo& info);
        static void reconnectInputSource(qv::NodeBase* node, const std::string& inputName, const std::vector<qv::NodeOutputInfo>& inputInfos, int index);
        static void getForwardNodeInfos(qv::NodeBase* node, std::vector<NodeInfo>& infos);
        static NodePrecondition getNodePrecondition(qv::NodeBase* node);
        static void setNodePrecondition(qv::NodeBase* node, const NodePrecondition& precondition);

    public:
        std::vector<std::unique_ptr<qv::NodeBase>> nodes;
        //std::vector<ResultDrawingInfo> drawingInfos;
        NodeConnection connection;
        ResultOutputPacket outputPacket;

    protected:
        std::map<std::string, bool> m_runResultMap;
        bool checkPrecondition(const std::string& guid);    //判断是否满足当前节点运行的前提条件
        static bool checkIsPreProcessNode(int id);

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(isEnable);
            ar& BOOST_SERIALIZATION_NVP(guid);
            ar& BOOST_SERIALIZATION_NVP(name);
            ar& BOOST_SERIALIZATION_NVP(description);

            ar& BOOST_SERIALIZATION_NVP(referImage);
            ar& BOOST_SERIALIZATION_NVP(connection);
            ar& BOOST_SERIALIZATION_NVP(outputPacket);
            ar& BOOST_SERIALIZATION_NVP(nodes);

            recoverNodes(); //恢复节点的连接关系
        }

    };

}