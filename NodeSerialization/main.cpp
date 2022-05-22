// NodeSerialization.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <memory>

#include <boost/serialization/serialization.hpp>

#include "serialization.h"
#include "nodeBase.h"
#include "node_A.h"
#include "node_B.h"
#include "node_C.h"

using namespace std;

void test1();
void test2();
void test3();
void test4();

int main()
{
    //测试基准
    std::cout << "test1...." << std::endl;
    test1();

    //测试派生类
    std::cout << "test2...." << std::endl;
    test2();

    //测试智能指针(shared)
    std::cout << "test3...." << std::endl;
    test3();

    //测试智能指针(unique)
    std::cout << "test4...." << std::endl;
    test4();
    
	return 0;
}

void test1()
{
    NodeBase* nodeBase = new NodeBase();
    nodeBase->nodeID = 1;
    serializeObj(nodeBase, "_1.pp");
    NodeBase* nodeBase2 = new NodeBase();
    deserializeObj(nodeBase2, "_1.pp");
    cout << nodeBase2->nodeID << endl;

}

//基类与派生类测试
void test2()
{
    NodeBase* node1 = new NodeA();
    node1->run();
    serializeObj(node1, "_2_1.pp");
    NodeBase* node2 = new NodeB();
    node2->run();
    serializeObj(node2, "_2_2.pp");
    NodeBase* node3 = new NodeC();
    node3->run();
    serializeObj(node3, "_2_3.pp");

    NodeBase* node11 = new NodeBase();
    deserializeObj(node11, "_2_1.pp");
    if (node11 != nullptr)
    {
        node11->run();
    }
    else
    {
        std::cout << "node11 is null" << std::endl;
    }

    NodeBase* node21 = new NodeBase();
    deserializeObj(node21, "_2_2.pp");
    if (node21 != nullptr)
    {
        node21->run();
    }
    else
    {
        std::cout << "node21 is null" << std::endl;
    }

    NodeBase* node31 = new NodeBase();
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
    std::shared_ptr<NodeBase> node1 = std::make_shared<NodeA>();
    serializeObj(node1, "_3_1.pp");
    std::shared_ptr<NodeBase> node2 = std::make_shared<NodeB>();
    serializeObj(node2, "_3_2.pp");
    std::shared_ptr<NodeBase> node3 = std::make_shared<NodeC>();
    serializeObj(node3, "_3_3.pp");
    
    std::shared_ptr<NodeBase> node11;
    deserializeObj(node11, "_3_1.pp");
    node11->run();
    std::shared_ptr<NodeBase> node21;
    deserializeObj(node21, "_3_2.pp");
    node21->run();
    std::shared_ptr<NodeBase> node31;
    deserializeObj(node31, "_3_3.pp");
    node31->run();

}


//测试在智能指针下的类型
void test4()
{
    std::unique_ptr<NodeBase> node1 = std::make_unique<NodeA>();
    serializeObj(node1, "_4_1.pp");
    std::unique_ptr<NodeBase> node2 = std::make_unique<NodeB>();
    serializeObj(node2, "_4_2.pp");
    std::unique_ptr<NodeBase> node3 = std::make_unique<NodeC>();
    serializeObj(node3, "_4_3.pp");

    std::unique_ptr<NodeBase> node11;
    deserializeObj(node11, "_4_1.pp");
    node11->run();
    std::unique_ptr<NodeBase> node21;
    deserializeObj(node21, "_4_2.pp");
    node21->run();
    std::unique_ptr<NodeBase> node31;
    deserializeObj(node31, "_4_3.pp");
    node31->run();

}
