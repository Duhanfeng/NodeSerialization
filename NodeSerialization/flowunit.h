#pragma once

#include "nodeBase.h"
#include <vector>
#include <memory>
#include <iostream>

class FlowUnit
{
public:
    std::vector<std::unique_ptr<NodeBase>> nodes;

    virtual void run()
    {
        std::cout << "FlowUnit size:" << nodes.size() << std::endl;

        for (size_t i = 0; i < nodes.size(); i++)
        {
            nodes[i]->run();
        }

    }


private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& BOOST_SERIALIZATION_NVP(nodes);
    }

};
