#include <iostream>
#include <memory>

#include <boost/serialization/serialization.hpp>
#include <opencv2/opencv.hpp>

#include <QEyeVisionLibrary/QEyeVisionLib.hpp>
#include <QEyeVisionLibraryNode/QEyeVisionLibraryNode.hpp>

#include "serialization.h"
#include "nodeBase.h"
#include "node_A.h"
#include "node_B.h"
#include "node_C.h"
#include "flowunit.h"
//BOOST_CLASS_EXPORT(qv::SmoothnessNode)

//#include "qeyeTest.h"

using namespace std;

void test1();
void test2();
void test3();
void test4();
void test5();
void test_remat();
void test_var();
void tesetNode1();
void testFlowUnit();

#define serializeObj serializeBin
#define deserializeObj deserializeBin

//#define serializeObj serializeText
//#define deserializeObj deserializeText

//#define serializeObj serializeXml
//#define deserializeObj deserializeXml

int main()
{
    ////测试基准
    //std::cout << "test1...." << std::endl;
    //test1();

    ////测试派生类
    //std::cout << "test2...." << std::endl;
    //test2();

    ////测试智能指针(shared)
    //std::cout << "test3...." << std::endl;
    //test3();

    ////测试智能指针(unique)
    //std::cout << "test4...." << std::endl;
    //test4();

    ////测试流程单元
    //std::cout << "test5...." << std::endl;
    //test5();

    ////测试图片序列化
    std::cout << "test_remat...." << std::endl;
    test_remat();

    ////测试变量
    //std::cout << "test_var...." << std::endl;
    //test_var();

    //std::cout << "tesetNode1...." << std::endl;
    //tesetNode1();

    std::cout << "testFlowUnit...." << std::endl;
    testFlowUnit();

    std::cout << "test finish" << std::endl;

	return 0;
}

void test1()
{
    //Node* nodeBase = new Node();
    //nodeBase->nodeID = 1;
    //serializeObj(nodeBase, "_1.pp");
    //Node* nodeBase2;
    //deserializeObj(nodeBase2, "_1.pp");
    //cout << nodeBase2->nodeID << endl;

}

//基类与派生类测试
void test2()
{
    Node* node1 = new NodeA();
    node1->run();
    serializeObj(node1, "_2_1.pp");
    Node* node2 = new NodeB();
    node2->run();
    serializeObj(node2, "_2_2.pp");
    Node* node3 = new NodeC();
    node3->run();
    serializeObj(node3, "_2_3.pp");

    Node* node11;
    deserializeObj(node11, "_2_1.pp");
    if (node11 != nullptr)
    {
        node11->run();
    }
    else
    {
        std::cout << "node11 is null" << std::endl;
    }

    Node* node21;
    deserializeObj(node21, "_2_2.pp");
    if (node21 != nullptr)
    {
        node21->run();
    }
    else
    {
        std::cout << "node21 is null" << std::endl;
    }

    Node* node31;
    deserializeObj(node31, "_2_3.pp");
    if (node31 != nullptr)
    {
        node31->run();
    }
    else
    {
        std::cout << "node31 is null" << std::endl;
    }

}

//测试在智能指针下的类型
void test3()
{
    std::shared_ptr<Node> node1 = std::make_shared<NodeA>();
    serializeObj(node1, "_3_1.pp");
    std::shared_ptr<Node> node2 = std::make_shared<NodeB>();
    serializeObj(node2, "_3_2.pp");
    std::shared_ptr<Node> node3 = std::make_shared<NodeC>();
    serializeObj(node3, "_3_3.pp");
    
    std::shared_ptr<Node> node11;
    deserializeObj(node11, "_3_1.pp");
    node11->run();
    std::shared_ptr<Node> node21;
    deserializeObj(node21, "_3_2.pp");
    node21->run();
    std::shared_ptr<Node> node31;
    deserializeObj(node31, "_3_3.pp");
    node31->run();

}

//测试在智能指针下的类型
void test4()
{
    std::unique_ptr<Node> node1 = std::make_unique<NodeA>();
    serializeObj(node1, "_4_1.pp");
    std::unique_ptr<Node> node2 = std::make_unique<NodeB>();
    serializeObj(node2, "_4_2.pp");
    std::unique_ptr<Node> node3 = std::make_unique<NodeC>();
    serializeObj(node3, "_4_3.pp");

    std::unique_ptr<Node> node11;
    deserializeObj(node11, "_4_1.pp");
    node11->run();
    std::unique_ptr<Node> node21;
    deserializeObj(node21, "_4_2.pp");
    node21->run();
    std::unique_ptr<Node> node31;
    deserializeObj(node31, "_4_3.pp");
    node31->run();

}

//测试流程单元
void test5()
{
    std::shared_ptr<FlowUnit> flowUnit = std::make_shared<FlowUnit>();
    flowUnit->nodes.emplace_back(std::make_unique<NodeC>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeC>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeA>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeC>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeB>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeA>());
    flowUnit->nodes.emplace_back(std::make_unique<NodeA>());
    flowUnit->run();

    //保存
    serializeObj(flowUnit, "_5_flowUnit.pp");

    //重新加载
    std::shared_ptr<FlowUnit> flowUnit2;
    deserializeObj(flowUnit2, "_5_flowUnit.pp");
    flowUnit2->run();

}

void test_remat()
{
    cv::Mat image = cv::imread("1.bmp");

    //保存
    serializeObj(image, "image.pp");

    //重新加载
    cv::Mat image2;
    deserializeObj(image2, "image.pp");

    if (!image2.empty())
    {
        cv::imshow("", image2);
        cv::waitKey();
    }
    else
    {

    }

}

void test_var()
{
    qv::Variant var0;
    qv::Variant var1(0);
    qv::Variant var2(0.1);
    qv::Variant var3("你好");
    qv::Variant var4(rv::Point<double>(10, 10));

    //保存
    ::serializeObj(var0, "_var_0.pp");
    ::serializeObj(var1, "_var_1.pp");
    ::serializeObj(var2, "_var_2.pp");
    ::serializeObj(var3, "_var_3.pp");
    ::serializeObj(var4, "_var_4.pp");

    //重新加载
    qv::Variant _var0;
    qv::Variant _var1;
    qv::Variant _var2;
    qv::Variant _var3;
    qv::Variant _var4;
    ::deserializeObj(_var0, "_var_0.pp");
    ::deserializeObj(_var1, "_var_1.pp");
    ::deserializeObj(_var2, "_var_2.pp");
    ::deserializeObj(_var3, "_var_3.pp");
    ::deserializeObj(_var4, "_var_4.pp");



}

void tesetNode1()
{
    //qv::NodeBase* node = new qv::SmoothnessNode();
    //node->nodeID = 9999;
    //node->description = "132455513355";
    //std::cout << node->nodeID << std::endl;
    //std::cout << node->description << std::endl;
    ////node->write("_node.pp");
    //serializeObj(node, "_node.pp");
    //qv::NodeBase* node2;
    //deserializeObj(node2, "_node.pp");
    //std::cout << node2->nodeID << std::endl;
    //std::cout << node2->description << std::endl;
    //node2->runImage(rv::ReMat(), nullptr);

    //构造对象
    qv::NodeBase* node = qv::NodeFactory::getInstance().createNode(qv::NodeIDEnum::Threshold);
    if (node == nullptr)
    {
        std::cout << "create Smoothness node error!" << std::endl;
        return;
    }
    node->nodeID = 9999;
    node->description = "132455513355";

    //测试文本格式
    qv::serializeText(node, "_qv_node_text.pp");
    {
        qv::NodeBase* node2;
        qv::deserializeText(node2, "_qv_node_text.pp");
        std::cout << node2->nodeID << std::endl;
        std::cout << node2->description << std::endl;
    }

    //测试二进制格式
    qv::serializeBin(node, "_qv_node_bin.pp");
    {
        qv::NodeBase* node2;
        qv::deserializeBin(node2, "_qv_node_bin.pp");
        std::cout << node2->nodeID << std::endl;
        std::cout << node2->description << std::endl;
    }

    //测试XML格式
    qv::serializeXml(node, "_qv_node_xml.pp");
    {
        qv::NodeBase* node2;
        qv::deserializeXml(node2, "_qv_node_xml.pp");
        std::cout << node2->nodeID << std::endl;
        std::cout << node2->description << std::endl;
    }

}

void testFlowUnit()
{
    qv::NodeBase* node1 =qv::NodeFactory::getInstance().createNode(qv::NodeIDEnum::Smoothness);
    qv::NodeBase* node2 =qv::NodeFactory::getInstance().createNode(qv::NodeIDEnum::Threshold);
    qv::NodeBase* node3 =qv::NodeFactory::getInstance().createNode(qv::NodeIDEnum::Morphology);

    std::shared_ptr<qv::FlowUnit> flowUnit = make_shared<qv::FlowUnit>();
    flowUnit->appendNode(std::unique_ptr<qv::NodeBase>(node1));
    flowUnit->appendNode(std::unique_ptr<qv::NodeBase>(node2));
    flowUnit->appendNode(std::unique_ptr<qv::NodeBase>(node3));

    rv::ReMat image("1.bmp");
    flowUnit->setReferImage(image);
    flowUnit->run((rv::IReWindow*)nullptr);

    //序列化
    qv::serializeText(flowUnit, "_qv_flowunit_text.pp");
    {
        std::shared_ptr<qv::FlowUnit> flowUnit2;
        qv::deserializeText(flowUnit2, "_qv_flowunit_text.pp");
        if (flowUnit2 != nullptr)
        {
            cv::imshow("referImage1", flowUnit2->referImage.getMat());
            cv::waitKey();
        }
        else
        {
            std::cout << "flowUnit deserializeText null" << std::endl;
        }
    }

    //序列化
    qv::serializeBin(flowUnit, "_qv_flowunit_bin.pp");
    {
        std::shared_ptr<qv::FlowUnit> flowUnit2;
        qv::deserializeBin(flowUnit2, "_qv_flowunit_bin.pp");
        if (flowUnit2 != nullptr)
        {
            cv::imshow("referImage2", flowUnit2->referImage.getMat());
            cv::waitKey();
        }
        else
        {
            std::cout << "flowUnit deserializeBin null" << std::endl;
        }
    }

    //序列化
    qv::serializeXml(flowUnit, "_qv_flowunit_xml.pp");
    {
        std::shared_ptr<qv::FlowUnit> flowUnit2;
        qv::deserializeXml(flowUnit2, "_qv_flowunit_xml.pp");
        if (flowUnit2 != nullptr)
        {
            cv::imshow("referImage3", flowUnit2->referImage.getMat());
            cv::waitKey();
        }
        else
        {
            std::cout << "flowUnit deserializeXml null" << std::endl;
        }
    }
}
