#pragma once

#include <boost/serialization/serialization.hpp>
#include <iostream>

class Node
{
public:
    bool isEnable = true;
    std::string guid;
    std::string name;
    std::string description = "";
    int nodeID = -1;

    virtual void run() = 0;

private:

private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        //ar& BOOST_SERIALIZATION_NVP(isEnable);
        //ar& BOOST_SERIALIZATION_NVP(guid);
        //ar& BOOST_SERIALIZATION_NVP(name);
        //ar& BOOST_SERIALIZATION_NVP(description);
        //ar& BOOST_SERIALIZATION_NVP(nodeID);

        ar& BOOST_SERIALIZATION_NVP(isEnable);
        ar& BOOST_SERIALIZATION_NVP(guid);
        ar& BOOST_SERIALIZATION_NVP(name);
        ar& BOOST_SERIALIZATION_NVP(description);
        ar& BOOST_SERIALIZATION_NVP(nodeID);
    }

};

#include <boost/serialization/export.hpp>
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node)
BOOST_CLASS_EXPORT_KEY(Node)

//BOOST_CLASS_EXPORT(Node)
//BOOST_CLASS_EXPORT_KEY(Node)
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node)
