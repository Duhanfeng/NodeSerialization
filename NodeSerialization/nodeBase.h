#pragma once

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>

class NodeBase
{
public:
    bool isEnable = true;
    std::string guid;
    std::string name;
    std::string description = "";
    int nodeID = -1;

    virtual void run() 
    {
        std::cout << "NodeBase" << std::endl;
    };

private:

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& isEnable;
        ar& guid;
        ar& name;
        ar& description;
        ar& nodeID;
    }

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(NodeBase)
