#pragma once

#include <iostream>
#include "nodeBase.h"

class NodeA : public Node
{
public:
    NodeA() : Node()
    {

    }

    virtual void run() override
    {
        std::cout << "NodeA" << std::endl;
    };


public:
    int valueA = 20;

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Node);

        ar& BOOST_SERIALIZATION_NVP(valueA);
    }

};

BOOST_CLASS_EXPORT(NodeA)
