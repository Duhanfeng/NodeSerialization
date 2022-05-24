#pragma once

#include <iostream>
#include "nodeBase.h"

class NodeA : public Node
{
public:
    NodeA() : Node()
    {

    }

    virtual void run() override;

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

////BOOST_CLASS_EXPORT(NodeA)
//#include <boost/serialization/export.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
BOOST_CLASS_EXPORT_KEY(NodeA)