#pragma once

#include <iostream>
#include "nodeBase.h"

class NodeB : public NodeBase
{
public:
    NodeB() : NodeBase()
    {

    }

    virtual void run() override
    {
        std::cout << "NodeB" << std::endl;
    };


public:
    int valueB = 20;

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);

        ar& valueB;
    }

};

BOOST_CLASS_EXPORT(NodeB)