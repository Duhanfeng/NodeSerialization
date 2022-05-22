#pragma once

#include <iostream>
#include "nodeBase.h"

class NodeC : public NodeBase
{
public:
    NodeC() : NodeBase()
    {

    }

    virtual void run() override
    {
        std::cout << "NodeC" << std::endl;
    };


public:
    int valueC = 20;

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);

        ar& BOOST_SERIALIZATION_NVP(valueC);
    }

};

BOOST_CLASS_EXPORT(NodeC)